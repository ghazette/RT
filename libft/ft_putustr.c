/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putustr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/26 10:52:37 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/31 10:38:55 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_putustr(wchar_t *str)
{
	while (*str)
	{
		if (*str <= 127)
			ft_putchar((char)*str);
		else if (*str >= 128 && *str <= 1114111)
			ft_putuchar(*str);
		str++;
	}
}
