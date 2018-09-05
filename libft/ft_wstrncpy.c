/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_wstrncpy.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/12 11:33:01 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/31 09:50:03 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

/*
** works like ft_wstrcpy but you can specify a limit
** copy src string into dest and return it
*/

wchar_t		*ft_wstrncpy(wchar_t *dest, const wchar_t *src, size_t n)
{
	wchar_t *dst;

	dst = dest;
	while (*src != L'\0' && n--)
		*dst++ = *src++;
	*dst = L'\0';
	return (dest);
}
