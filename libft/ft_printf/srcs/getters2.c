/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   getters2.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/19 18:43:07 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/24 17:50:19 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int			get_flag(const char *str, size_t len, t_prtfdata **elem)
{
	int flag;

	flag = 0;
	while (str[len] != '%')
	{
		if (str[len] == 'h' && str[len + 1] == 'h')
			flag = ((flag < FLAGS_HH) ? FLAGS_HH : flag);
		if (str[len] == 'h' && str[len + 1] != 'h')
			flag = ((flag < FLAGS_H) ? FLAGS_H : flag);
		if (str[len] == 'l' && str[len + 1] == 'l')
			flag = ((flag < FLAGS_LL) ? FLAGS_LL : flag);
		if (str[len] == 'l' && str[len + 1] != 'l')
			flag = ((flag < FLAGS_L) ? FLAGS_L : flag);
		if (str[len] == 'j')
			flag = ((flag < FLAGS_J) ? FLAGS_J : flag);
		if (str[len] == 'z')
			flag = ((flag < FLAGS_Z) ? FLAGS_Z : flag);
		len--;
	}
	if ((*elem)->format == 'c' && flag == FLAGS_L)
		(*elem)->format = 'C';
	if ((*elem)->format == 's' && flag == FLAGS_L)
		(*elem)->format = 'S';
	return (flag);
}

int			get_htag(const char *str, size_t len, t_prtfdata **elem)
{
	if (ft_strchr("XxOo", (*elem)->format))
		while (str[len] != '%')
		{
			if (str[len] == '#')
				return (1);
			len--;
		}
	return (0);
}

int			get_precision(const char *str, size_t len, va_list args)
{
	int nb;

	nb = 0;
	while (str[len] != '%')
	{
		if (str[len] == '.')
		{
			if (str[len + 1] == '*')
			{
				nb = (int)va_arg(args, int);
				if (nb < 0)
					return (-1);
				return (nb);
			}
			return (ft_atoi(str + len + 1));
		}
		len--;
	}
	return (-1);
}

int			get_pluspad(const char *str, size_t len, t_prtfdata **elem)
{
	while (str[len] != '%')
	{
		if (str[len] == '+')
		{
			if (!ft_strchr("Ddi", (*elem)->format))
				return (0);
			return (1);
		}
		len--;
	}
	return (0);
}

void		get_rspaced(t_prtfdata **elm, const char *str, size_t len)
{
	while (str[len--] != '%' && (*elm)->rspace == 0)
		if (str[len] == '-')
		{
			(*elm)->rspace = (*elm)->lspace;
			(*elm)->lspace = 0;
			break ;
		}
}
