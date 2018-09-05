/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_wstrdup.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/12 11:33:33 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/31 10:29:40 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdlib.h>

/*
** works like ft_strdup but for wchar_t type
** allocated the correct size and return a fresh copy of the string
*/

wchar_t		*ft_wstrdup(const wchar_t *src)
{
	wchar_t *dst;

	dst = NULL;
	if (src)
	{
		dst = (wchar_t *)malloc(sizeof(wchar_t) * (ft_wcslen(src) + 1));
		if (!dst)
			return (NULL);
		dst = ft_wstrcpy(dst, src);
	}
	return (dst);
}
