/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_wstrcpy.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/12 11:32:24 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/31 09:48:47 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

/*
** works like ft_strcpy but for wchar_t type
** copy src string into dest and return it
*/

wchar_t		*ft_wstrcpy(wchar_t *dest, const wchar_t *src)
{
	wchar_t *dst;

	dst = dest;
	while (*src != L'\0')
		*dst++ = *src++;
	*dst = L'\0';
	return (dest);
}
