/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_di.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/16 18:51:45 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/31 11:55:44 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char		*remove_neg(char **str)
{
	char *tmp;

	if (!(tmp = ft_strdup(*str + 1)))
		return (NULL);
	ft_strdel(&(*str));
	if (!(*str = ft_strdup(tmp)))
		return (NULL);
	return (*str);
}

static int		parse_di_part1(t_prtfdata **elem, int *isneg)
{
	if ((*elem)->str.ch[0] == '0' && (*elem)->precision == 0)
	{
		ft_strdel(&((*elem)->str.ch));
		if (!((*elem)->str.ch = ft_strnew(0)))
			return (0);
	}
	*isneg = ((*elem)->str.ch[0] == '-') ? 1 : *isneg;
	if ((*elem)->str.ch[0] == '-')
		if (!((*elem)->str.ch = remove_neg(&((*elem)->str.ch))))
			return (0);
	(*elem)->len = ft_strlen((*elem)->str.ch);
	if ((*elem)->precision - (*elem)->len > 0)
		if (!((*elem)->str.ch = char_concat(&((*elem)->str.ch), '0',
			(*elem)->precision - (*elem)->len, LSPACE)))
			return (0);
	if (*isneg == 1)
		if (!((*elem)->str.ch = char_concat(&((*elem)->str.ch), '-', 1,
		LSPACE)))
			return (0);
	if ((*elem)->pluspad && *isneg == 0)
		if (!((*elem)->str.ch = char_concat(&((*elem)->str.ch), '+', 1,
		LSPACE)))
			return (0);
	return (1);
}

static int		parse_di_part2(t_prtfdata **elem, int isneg)
{
	(*elem)->len = ft_strlen((*elem)->str.ch);
	if ((*elem)->havespace == 1 && isneg == 0 && (*elem)->pluspad == 0 &&
		((*elem)->precision >= (*elem)->lspace || (*elem)->precision == -1))
	{
		(*elem)->len++;
		(*elem)->havespace = 2;
	}
	if ((*elem)->lspace - (*elem)->len > 0 && (*elem)->zeropad == 0)
		if (!((*elem)->str.ch = char_concat(&((*elem)->str.ch), ' ',
			(*elem)->lspace - (*elem)->len, LSPACE)))
			return (0);
	if ((*elem)->lspace - (*elem)->len > 0 && (*elem)->zeropad == 1)
	{
		if (!((*elem)->str.ch = char_concat(&((*elem)->str.ch), '0',
			(*elem)->lspace - (*elem)->len, LSPACE)))
			return (0);
		if ((*elem)->pluspad == 1 || isneg == 1)
		{
			(*elem)->str.ch[0] = (isneg == 1) ? '-' : '+';
			(*elem)->str.ch[(*elem)->lspace - (*elem)->len] = '0';
		}
	}
	return (1);
}

static int		parse_di_part3(t_prtfdata **elem)
{
	if ((*elem)->rspace - (*elem)->len > 0)
		if (!((*elem)->str.ch = char_concat(&((*elem)->str.ch), ' ',
			(*elem)->rspace - (*elem)->len, RSPACE)))
			return (0);
	if ((*elem)->havespace == 2)
		if (!((*elem)->str.ch = char_concat(&((*elem)->str.ch), ' ', 1,
		LSPACE)))
			return (0);
	return (1);
}

int				parse_di(t_prtfdata **elm)
{
	int	isneg;

	isneg = 0;
	if (!(parse_di_part1(&(*elm), &isneg)))
		return (0);
	if (!(parse_di_part2(&(*elm), isneg)))
		return (0);
	if (!(parse_di_part3(&(*elm))))
		return (0);
	(*elm)->len = ft_strlen((*elm)->str.ch);
	return (1);
}
