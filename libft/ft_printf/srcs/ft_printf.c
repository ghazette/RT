/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/20 11:01:59 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/31 11:54:02 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	core(t_prtfdata **elem, va_list args, const char *format,
	char **buffer)
{
	long long int len;

	len = format_parse(&(*elem), format + (*elem)->i, args);
	if (!(conv_and_parse(&(*elem), args)))
	{
		pops(&(*elem));
		return (-1);
	}
	buffer_display(&(*buffer), format, (*elem)->i, 0);
	if (len == 0)
		return ((*elem)->size);
	display(&(*elem));
	update(&(*elem), len);
	return (-2);
}

static int	core_loop(t_prtfdata **elem, const char *format, char **buffer,
	va_list args)
{
	long long int	size;
	long long int	res;

	while (format[(*elem)->i])
	{
		if (format[(*elem)->i] == '%')
		{
			if ((res = core(&(*elem), args, format, &(*buffer))) == -1)
				return (-1);
			if (res >= 0)
				return (res);
			continue ;
		}
		buffer_display(&(*buffer), format, (*elem)->i, 1);
		(*elem)->size++;
		(*elem)->i += (format[(*elem)->i] != '\0') ? 1 : 0;
	}
	buffer_display(&(*buffer), format, (*elem)->i, 0);
	size = (*elem)->size;
	pops(&(*elem));
	va_end(args);
	return (size);
}

int			ft_printf(const char *format, ...)
{
	va_list			args;
	char			*buffer;
	t_prtfdata		*elem;

	buffer = NULL;
	if (!(elem = create_elem()))
		return (-1);
	va_start(args, format);
	return (core_loop(&elem, format, &buffer, args));
}
