/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_cs_utf.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/19 16:19:19 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/23 18:56:59 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	check_c_utf(t_prtfdata **elm)
{
	char	tmp;

	if (MB_CUR_MAX == 1)
	{
		if ((*elm)->str.wch[0] >= 128 && (*elm)->str.wch[0] <= 255)
		{
			(*elm)->type = TYPE_CHAR;
			tmp = (char)((*elm)->str.wch[0]);
			free((*elm)->str.wch);
			if (!((*elm)->str.ch = (char*)malloc(2)))
				return (0);
			(*elm)->str.ch[0] = tmp;
			(*elm)->str.ch[1] = '\0';
			return (parse_c(&(*elm)));
		}
		if ((*elm)->str.wch[0] >= 256 || (*elm)->str.wch[0] < 0)
			return (0);
	}
	return (1);
}

int			parse_c_utf(t_prtfdata **elm)
{
	int c;
	int inc;

	inc = ((*elm)->str.wch[0] == '\0') ? 1 : 0;
	if (((*elm)->str.wch[0] >= 55296 && (*elm)->str.wch[0] <= 57343) ||
	((*elm)->str.wch[0] > 1114111 || (*elm)->str.wch[0] < 0))
		return (0);
	(*elm)->len = ft_getcbytesize((*elm)->str.wch[0]);
	if (!(check_c_utf(&(*elm))))
		return (0);
	if ((*elm)->rspace - (*elm)->len > 0)
		if (!((*elm)->str.wch = wchar_concat(&((*elm)->str.wch), ' ',
			(*elm)->rspace - (*elm)->len, RSPACE)))
			return (0);
	if ((*elm)->lspace - (*elm)->len > 0)
	{
		c = ((*elm)->zeropad == 1) ? '0' : ' ';
		if (!((*elm)->str.wch = wchar_concat(&((*elm)->str.wch), c,
		(*elm)->lspace - (*elm)->len, LSPACE)))
			return (0);
	}
	(*elm)->len = ((*elm)->type == TYPE_WCHAR) ?
	ft_getbytesize((*elm)->str.wch) + inc : ft_strlen((*elm)->str.ch) + inc;
	(*elm)->wlen = ft_wcslen((*elm)->str.wch) + inc;
	return (1);
}

static int	preci_s_utf(t_prtfdata **elm)
{
	int		i;
	int		size;
	wchar_t	*tmp;

	i = 0;
	size = 0;
	if ((*elm)->precision != -1)
	{
		while (MB_CUR_MAX == 4 && (*elm)->str.wch[i] != L'\0')
		{
			size += ft_getcbytesize((*elm)->str.wch[i]);
			i += (size == (*elm)->precision) ? 1 : 0;
			if (size >= (*elm)->precision)
				break ;
			i++;
		}
		i = (MB_CUR_MAX == 1) ? (*elm)->precision : i;
		if (!(tmp = ft_wstrndup((*elm)->str.wch, i)))
			return (0);
		free((*elm)->str.wch);
		if (!((*elm)->str.wch = ft_wstrdup(tmp)))
			return (0);
		free(tmp);
	}
	return (1);
}

static int	check_s_utf(t_prtfdata **elm)
{
	int	i;

	i = 0;
	while ((*elm)->str.wch[i] != L'\0')
	{
		if (MB_CUR_MAX == 1 && (*elm)->str.wch[i] >= 256)
			return (0);
		if (MB_CUR_MAX == 4 && ((*elm)->str.wch[i] >= 55296 &&
			(*elm)->str.wch[i] <= 57343))
			return (0);
		if ((*elm)->str.wch[i] < 0)
			return (0);
		i++;
	}
	i = 0;
	if (MB_CUR_MAX == 1)
		while ((*elm)->str.wch[i] != L'\0')
		{
			(*elm)->str.wch[i] = (char)(*elm)->str.wch[i];
			i++;
		}
	return (1);
}

int			parse_s_utf(t_prtfdata **elm)
{
	wchar_t c;

	c = L' ';
	if (!(preci_s_utf(&(*elm))))
		return (0);
	if (!(check_s_utf(&(*elm))))
		return (0);
	(*elm)->len = ft_getbytesize((*elm)->str.wch);
	if ((*elm)->rspace - (*elm)->len > 0)
		if (!((*elm)->str.wch = wchar_concat(&((*elm)->str.wch), ' ',
			(*elm)->rspace - (*elm)->len, RSPACE)))
			return (0);
	if ((*elm)->lspace - (*elm)->len > 0)
	{
		c = ((*elm)->zeropad == 1) ? L'0' : L' ';
		if (!((*elm)->str.wch = wchar_concat(&((*elm)->str.wch), c,
		(*elm)->lspace - (*elm)->len, LSPACE)))
			return (0);
	}
	(*elm)->len = ft_getbytesize((*elm)->str.wch);
	return (1);
}
