/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   getters.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/11 17:53:31 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/24 18:02:29 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int			get_format(const char *str, size_t *len)
{
	*len = 0;
	while (str[*len])
	{
		*len += 1;
		if (str[*len] == '%')
			break ;
		if (!(ft_strchr("0123456789 -.#+lzjh*", str[*len])))
			break ;
	}
	return (str[*len]);
}

static void			get_space(t_prtfdata **elm, const char *str, size_t len,
	va_list args)
{
	size_t		len2;
	int			nb;

	while (str[len] != '%')
	{
		len2 = len;
		if (str[len] == '*' && str[len - 1] != '.')
		{
			nb = (int)va_arg(args, int);
			(*elm)->rspace = (nb < 0) ? -nb : 0;
			(*elm)->lspace = (nb > 0) ? nb : 0;
			break ;
		}
		if (ft_isdigit(str[len]))
		{
			while (ft_isdigit(str[len2]) && str[len2] != '%')
				len2--;
			if (str[len2] != '.')
				if (((*elm)->lspace = ft_atoi(str + len2 + 1)) != 0)
					purge(str, &len2, args);
		}
		len -= (len == len2) ? 1 : (len - len2);
	}
}

static int			get_zeropad(const char *str, size_t len, t_prtfdata **elem)
{
	if (((*elem)->precision != -1 && (*elem)->lspace > 0) &&
		ft_strchr("Ddi", (*elem)->format))
		return (0);
	while (str[len] != '%')
	{
		if (!(ft_strchr("0123456789.-", str[len - 1])) &&
			str[len] == '0' && str[len + 1] != '-')
			return (1);
		len--;
	}
	return (0);
}

static int			get_uniquespace(const char *str, size_t len,
	t_prtfdata **elem)
{
	while (str[len] != '%')
	{
		if (str[len] == ' ')
		{
			if (ft_strchr("Ddi", (*elem)->format) && (*elem)->pluspad == 0)
				return (1);
			return (0);
		}
		len--;
	}
	return (0);
}

size_t				format_parse(t_prtfdata **elm, const char *str,
				va_list args)
{
	size_t		len;
	t_prtfdata	*elem;

	elem = *elm;
	elem->format = get_format(str, &len);
	if (elem->format == '\0')
	{
		elem->type = 0;
		elem->len = 0;
		return (0);
	}
	len -= (elem->format == '%') ? 1 : 0;
	elem->flag = get_flag(str, len, &(*elm));
	elem->htag = get_htag(str, len, &(*elm));
	get_space(&(*elm), str, len, args);
	get_rspaced(&(*elm), str, len);
	elem->precision = get_precision(str, len, args);
	elem->pluspad = get_pluspad(str, len, &(*elm));
	elem->havespace = get_uniquespace(str, len, &(*elm));
	elem->zeropad = get_zeropad(str, len, &(*elm));
	len += (elem->format == '%') ? 1 : 0;
	return (len + 1);
}
