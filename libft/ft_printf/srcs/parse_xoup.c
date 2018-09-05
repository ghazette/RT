/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_xoup.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/18 11:47:06 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/23 13:18:49 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int		parse_xoup_part1(t_prtfdata **elm)
{
	int iszero;

	iszero = ((*elm)->str.ch[0] == '0') ? 1 : 0;
	(*elm)->len = ft_strlen((*elm)->str.ch);
	if (iszero == 1 && (*elm)->precision == 0 &&
	ft_strchr("Xx", (*elm)->format))
	{
		ft_strdel(&((*elm)->str.ch));
		if (!((*elm)->str.ch = ft_strnew(0)))
			return (0);
	}
	if ((*elm)->htag == 0 && iszero == 1 && (*elm)->precision == 0)
	{
		ft_strdel(&((*elm)->str.ch));
		if (!((*elm)->str.ch = ft_strnew(0)))
			return (0);
	}
	if ((*elm)->htag == 1 && ft_strchr("Oo", (*elm)->format) && iszero == 0)
	{
		if (!((*elm)->str.ch = char_concat(&((*elm)->str.ch), '0', 1, LSPACE)))
			return (0);
		(*elm)->len = ft_strlen((*elm)->str.ch);
	}
	(*elm)->htag = (iszero == 1) ? 0 : (*elm)->htag;
	return (1);
}

static int		parse_xoup_part2(t_prtfdata **elm)
{
	if ((*elm)->precision - (*elm)->len > 0)
		if (!((*elm)->str.ch = char_concat(&((*elm)->str.ch), '0',
			(*elm)->precision - (*elm)->len, LSPACE)))
			return (0);
	if (((*elm)->htag == 1 && ft_strchr("Xx", (*elm)->format)) ||
		(*elm)->format == 'p')
	{
		if (!((*elm)->str.ch = char_concat(&((*elm)->str.ch), ' ', 2, LSPACE)))
			return (0);
		(*elm)->str.ch[0] = '0';
		(*elm)->str.ch[1] = 'x';
	}
	(*elm)->len = ft_strlen((*elm)->str.ch);
	if ((*elm)->rspace - (*elm)->len > 0)
		if (!((*elm)->str.ch = char_concat(&((*elm)->str.ch), ' ',
			(*elm)->rspace - (*elm)->len, RSPACE)))
			return (0);
	if ((*elm)->lspace - (*elm)->len > 0 && (*elm)->zeropad == 0)
		if (!((*elm)->str.ch = char_concat(&((*elm)->str.ch), ' ',
		(*elm)->lspace - (*elm)->len, LSPACE)))
			return (0);
	return (1);
}

static int		parse_xoup_part3(t_prtfdata **elm)
{
	int i;

	i = 2;
	if ((*elm)->lspace - (*elm)->len > 0 && (*elm)->zeropad == 1 &&
		(*elm)->precision == -1)
	{
		if (!((*elm)->str.ch = char_concat(&((*elm)->str.ch), '0',
			(*elm)->lspace - (*elm)->len, LSPACE)))
			return (0);
		if ((ft_strchr("Xx", (*elm)->format) && (*elm)->htag == 1) ||
			(*elm)->format == 'p')
		{
			(*elm)->str.ch[1] = 'x';
			while ((*elm)->str.ch[i] == '0')
				i++;
			(*elm)->str.ch[i] = '0';
		}
	}
	if ((*elm)->format == 'X')
		ft_strupcase((*elm)->str.ch);
	return (1);
}

int				parse_xoup(t_prtfdata **elm)
{
	if ((*elm)->precision != -1)
		(*elm)->zeropad = 0;
	if (!(parse_xoup_part1(&(*elm))))
		return (0);
	if (!(parse_xoup_part2(&(*elm))))
		return (0);
	if (!(parse_xoup_part3(&(*elm))))
		return (0);
	(*elm)->len = ft_strlen((*elm)->str.ch);
	return (1);
}
