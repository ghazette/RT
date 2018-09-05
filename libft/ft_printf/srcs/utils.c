/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/27 15:09:21 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/31 11:54:47 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int			purge(const char *str, size_t *len2, va_list args)
{
	int	nb;

	while (str[*len2] != '%')
	{
		nb = (str[*len2] == '*' && str[*len2 - 1] != '.') ?
		(int)va_arg(args, int) : 0;
		(*len2)--;
	}
	return (nb);
}

char		*char_concat(char **str, int c, size_t n, int lrspace)
{
	char *add;
	char *tmp;

	if (n > 0)
	{
		if (!(add = ft_newcstr(c, n)))
			return (NULL);
		if (lrspace == LSPACE)
			if (!(tmp = ft_strjoin(add, *str)))
				return (NULL);
		if (lrspace == RSPACE)
			if (!(tmp = ft_strjoin(*str, add)))
				return (NULL);
		ft_strdel(&add);
		ft_strdel(&(*str));
		if (!(*str = ft_strdup(tmp)))
			return (NULL);
		ft_strdel(&tmp);
	}
	return (*str);
}

wchar_t		*wchar_concat(wchar_t **str, int c, size_t n, int lrspace)
{
	wchar_t *tmp;
	wchar_t *add;

	if (n > 0)
	{
		if (!(add = ft_newcwstr(c, n)))
			return (NULL);
		if (lrspace == LSPACE)
			if (!(tmp = ft_wstrjoin(add, *str)))
				return (NULL);
		if (lrspace == RSPACE)
			if (!(tmp = ft_wstrjoin(*str, add)))
				return (NULL);
		free(*str);
		free(add);
		if (!(*str = ft_wstrdup(tmp)))
			return (NULL);
		free(tmp);
	}
	return (*str);
}

size_t		ft_getcbytesize(wchar_t c)
{
	if (c <= 127)
		return (1);
	if (c >= 128 && c <= 2047)
		return (2);
	if (c >= 2048 && c <= 65535)
		return (3);
	if (c >= 65536 && c <= 1114111)
		return (4);
	return (0);
}

size_t		ft_getbytesize(wchar_t *data)
{
	size_t	i;
	size_t	size;
	wchar_t	*str;

	i = 0;
	size = 0;
	str = (wchar_t*)data;
	while (str[i] != '\0')
	{
		size += ft_getcbytesize(str[i]);
		i++;
	}
	return (size);
}
