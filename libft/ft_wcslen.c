/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_wcslen.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/12 11:31:48 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/31 09:48:24 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

size_t		ft_wcslen(const wchar_t *str)
{
	const wchar_t *i;

	i = str;
	while (*i)
		i++;
	return (i - str);
}
