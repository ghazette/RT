/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   conv_and_parse.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/26 15:22:51 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/23 16:59:30 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	conv_int(t_prtfdata **elm, va_list args)
{
	long long int	n;
	t_prtfdata		*elem;

	elem = *elm;
	if (elem->format == 'D')
		elem->flag = FLAGS_LL;
	if (elem->flag == FLAGS_H)
		n = (short int)va_arg(args, long long int);
	else if (elem->flag == FLAGS_HH)
		n = (char)va_arg(args, long long int);
	else if (elem->flag == FLAGS_L)
		n = (long int)va_arg(args, long long int);
	else if (elem->flag == FLAGS_LL)
		n = (long long int)va_arg(args, long long int);
	else if (elem->flag == FLAGS_J)
		n = (intmax_t)va_arg(args, intmax_t);
	else if (elem->flag == FLAGS_Z)
		n = (size_t)va_arg(args, size_t);
	else
		n = (int)va_arg(args, long long int);
	elem->pluspad = (n < 0) ? 0 : elem->pluspad;
	if (!(conv(&(*elm), n, 0)))
		return (0);
	return (1);
}

int	conv_char(t_prtfdata **elm, va_list args)
{
	if ((*elm)->format == 'C')
	{
		if (!((*elm)->str.wch = ft_newcwstr('0', 1)))
			return (0);
		(*elm)->str.wch[0] = (wchar_t)va_arg(args, wchar_t);
		(*elm)->type = TYPE_WCHAR;
	}
	else if ((*elm)->format == 'c' || (*elm)->format == '%')
	{
		if (!((*elm)->str.ch = ft_strnew(1)))
			return (0);
		(*elm)->str.ch[0] = ((*elm)->format == 'c') ?
			(char)va_arg(args, int) : '%';
		if ((*elm)->str.ch[0] == '\0')
		{
			ft_strdel(&((*elm)->str.ch));
			if (!((*elm)->str.ch = ft_strnew(0)))
				return (0);
		}
	}
	return (1);
}

int	conv_uint(t_prtfdata **elm, va_list args)
{
	uintmax_t	n;
	t_prtfdata	*elem;

	elem = *elm;
	if (elem->flag == FLAGS_H)
		n = (unsigned short int)va_arg(args, uintmax_t);
	else if (elem->flag == FLAGS_HH)
		n = (unsigned char)va_arg(args, uintmax_t);
	else if (elem->flag == FLAGS_L)
		n = (unsigned long int)va_arg(args, uintmax_t);
	else if (elem->flag == FLAGS_LL)
		n = (unsigned long long int)va_arg(args, uintmax_t);
	else if (elem->flag == FLAGS_J)
		n = (uintmax_t)va_arg(args, uintmax_t);
	else if (elem->flag == FLAGS_Z)
		n = (size_t)va_arg(args, size_t);
	else
		n = (unsigned int)va_arg(args, uintmax_t);
	if (!(conv(&(*elm), 0, n)))
		return (0);
	return (1);
}

int	conv_lint(t_prtfdata **elm, va_list args)
{
	long long int	n;

	n = (long long int)va_arg(args, long long int);
	if (!(conv(&(*elm), n, 0)))
		return (0);
	return (1);
}

int	conv_ptr(t_prtfdata **elm, va_list args)
{
	size_t	ptr;

	if ((*elm)->format == 's')
		if (!((*elm)->str.ch = ft_strdup((char*)va_arg(args, char *))))
			if (!((*elm)->str.ch = ft_strdup("(null)")))
				return (0);
	if ((*elm)->format == 'S')
	{
		if (!((*elm)->str.wch = ft_wstrdup((wchar_t*)va_arg(args, wchar_t *))))
			if (!((*elm)->str.wch = ft_wstrdup(L"(null)")))
				return (0);
		(*elm)->type = TYPE_WCHAR;
	}
	if ((*elm)->format == 'p')
	{
		ptr = (size_t)va_arg(args, size_t);
		if (!((*elm)->str.ch = ft_itoa_base(ptr, 16)))
			return (0);
	}
	return (1);
}
