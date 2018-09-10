/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   display.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/24 10:51:09 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/24 18:17:38 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	*ft_fill_buff(const char *str)
{
	int		i;
	int		j;
	char	*buf;

	buf = NULL;
	i = 0;
	j = 0;
	while (str[j] != '%' && str[j])
		j++;
	if (!(buf = ft_strnew(j)))
		return (NULL);
	while (i < j)
	{
		buf[i] = str[i];
		i++;
	}
	buf[i] = '\0';
	return (buf);
}

void		display(t_prtfdata **elm)
{
	if ((*elm)->type == TYPE_CHAR && (*elm)->format == 'c')
	{
		if ((*elm)->lspace >= 0 && (*elm)->rspace == 0)
			ft_putstr((*elm)->str.ch);
		if ((*elm)->str.ch[(*elm)->len - 1] == '\0')
			ft_putchar('\0');
		if ((*elm)->rspace > 0)
			ft_putstr((*elm)->str.ch);
	}
	else if ((*elm)->type == TYPE_CHAR)
		write(1, (*elm)->str.ch, (*elm)->len);
	else if ((*elm)->type == TYPE_WCHAR && (*elm)->format == 'C')
	{
		if ((*elm)->lspace >= 0 && (*elm)->rspace == 0)
			ft_putustr((*elm)->str.wch);
		if ((*elm)->str.wch[(*elm)->wlen - 1] == L'\0')
			ft_putchar('\0');
		if ((*elm)->rspace > 0)
			ft_putustr((*elm)->str.wch);
	}
	else if ((*elm)->type == TYPE_WCHAR)
		ft_putustr((*elm)->str.wch);
}

void		buffer_display(char **buffer, const char *format,
	long long int i, int action)
{
	size_t len;

	if (action == 0)
	{
		if (*buffer)
		{
			len = ft_strlen(*buffer);
			write(1, *buffer, len);
			ft_strdel(&(*buffer));
		}
	}
	if (action == 1)
	{
		if (!*buffer)
			*buffer = ft_fill_buff(format + i);
	}
}
