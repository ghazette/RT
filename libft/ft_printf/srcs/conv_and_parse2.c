/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   conv_and_parse2.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/26 15:22:51 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/24 17:01:11 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	conv(t_prtfdata **elm, intmax_t n, uintmax_t nu)
{
	if (ft_strchr("Ddi", (*elm)->format))
		if (!((*elm)->str.ch = ft_itoa(n)))
			return (0);
	if ((*elm)->format == 'x' || (*elm)->format == 'X')
		if (!((*elm)->str.ch = ft_uitoa_base(nu, 16)))
			return (0);
	if ((*elm)->format == 'o')
		if (!((*elm)->str.ch = ft_uitoa_base(nu, 8)))
			return (0);
	if ((*elm)->format == 'u')
		if (!((*elm)->str.ch = ft_uitoa(nu)))
			return (0);
	if ((*elm)->format == 'O')
		if (!((*elm)->str.ch = ft_uitoa_base(n, 8)))
			return (0);
	if ((*elm)->format == 'U')
		if (!((*elm)->str.ch = ft_uitoa(n)))
			return (0);
	return (1);
}

int	conv_notype(t_prtfdata **elm)
{
	if (!((*elm)->str.ch = ft_strnew(1)))
		return (0);
	(*elm)->str.ch[0] = (*elm)->format;
	return (1);
}

int	parse(t_prtfdata **elm)
{
	if ((*elm)->format == 'C')
		if (!(parse_c_utf(&(*elm))))
			return (0);
	if ((*elm)->format == 'S')
		if (!(parse_s_utf(&(*elm))))
			return (0);
	if ((*elm)->format == 's')
		if (!(parse_s(&(*elm))))
			return (0);
	if ((ft_strchr("Ddi", (*elm)->format)) != NULL)
		if ((parse_di(&(*elm))))
			return (1);
	if ((ft_strchr("pXxoOuU", (*elm)->format)) != NULL)
		if (!(parse_xoup(&(*elm))))
			return (0);
	if ((ft_strchr("c%", (*elm)->format)) != NULL)
		if (!(parse_c(&(*elm))))
			return (0);
	if (!(ft_strchr("nDdiXxouOUSspcC%", (*elm)->format)))
		if (!(parse_notype(&(*elm))))
			return (0);
	return (1);
}

int	conv_and_parse(t_prtfdata **elm, va_list args)
{
	if ((ft_strchr("Ddi", (*elm)->format)) != NULL)
		if ((!conv_int(&(*elm), args)))
			return (0);
	if ((ft_strchr("Xxou", (*elm)->format)) != NULL)
		if (!(conv_uint(&(*elm), args)))
			return (0);
	if ((ft_strchr("OU", (*elm)->format)) != NULL)
		if (!(conv_lint(&(*elm), args)))
			return (0);
	if ((ft_strchr("%Ssp", (*elm)->format)) != NULL)
		if (!(conv_ptr(&(*elm), args)))
			return (0);
	if ((ft_strchr("cC%", (*elm)->format)) != NULL)
		if (!(conv_char(&(*elm), args)))
			return (0);
	if ((*elm)->format == 'n')
		*((int*)va_arg(args, int*)) = (*elm)->size;
	if (!(ft_strchr("nDdiXxouOUSspcC%", (*elm)->format)))
		if (!(conv_notype(&(*elm))))
			return (0);
	if (!(parse(&(*elm))))
		return (0);
	return (1);
}
