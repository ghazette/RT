/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_cs.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/18 14:09:44 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/23 13:35:29 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		parse_c(t_prtfdata **elm)
{
	int c;
	int inc;

	inc = ((*elm)->str.ch[0] == '\0') ? 1 : 0;
	c = ' ';
	(*elm)->len = 1;
	if ((*elm)->rspace - (*elm)->len > 0)
	{
		if (!((*elm)->str.ch = char_concat(&((*elm)->str.ch), ' ',
			(*elm)->rspace - (*elm)->len, RSPACE)))
			return (0);
	}
	if ((*elm)->lspace - (*elm)->len > 0)
	{
		c = ((*elm)->zeropad == 1) ? '0' : ' ';
		if (!((*elm)->str.ch = char_concat(&((*elm)->str.ch), c,
		(*elm)->lspace - (*elm)->len, LSPACE)))
			return (0);
	}
	(*elm)->len = ft_strlen((*elm)->str.ch) + inc;
	return (1);
}

int		parse_s(t_prtfdata **elm)
{
	int c;

	c = ' ';
	(*elm)->len = ft_strlen((*elm)->str.ch);
	if ((*elm)->precision != -1)
		(*elm)->str.ch = ft_realloc((*elm)->str.ch, (*elm)->precision);
	(*elm)->len = ft_strlen((*elm)->str.ch);
	if ((*elm)->rspace - (*elm)->len > 0)
		if (!((*elm)->str.ch = char_concat(&((*elm)->str.ch), ' ',
			(*elm)->rspace - (*elm)->len, RSPACE)))
			return (0);
	if ((*elm)->lspace - (*elm)->len > 0)
	{
		c = ((*elm)->zeropad == 1) ? '0' : ' ';
		if (!((*elm)->str.ch = char_concat(&((*elm)->str.ch), c,
		(*elm)->lspace - (*elm)->len, LSPACE)))
			return (0);
	}
	(*elm)->len = ft_strlen((*elm)->str.ch);
	return (1);
}

int		parse_notype(t_prtfdata **elm)
{
	int c;

	c = ' ';
	(*elm)->len = 1;
	if ((*elm)->rspace - (*elm)->len > 0)
		if (!((*elm)->str.ch = char_concat(&((*elm)->str.ch), ' ',
			(*elm)->rspace - (*elm)->len, RSPACE)))
			return (0);
	if ((*elm)->lspace - (*elm)->len > 0)
	{
		c = ((*elm)->zeropad == 1) ? '0' : ' ';
		if (!((*elm)->str.ch = char_concat(&((*elm)->str.ch), c,
		(*elm)->lspace - (*elm)->len, LSPACE)))
			return (0);
	}
	(*elm)->len = ft_strlen((*elm)->str.ch);
	return (1);
}
