/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_wstrndup.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/12 11:34:00 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/31 10:30:52 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdlib.h>

/*
** works like ft_wstrdup but copy until \0 met, or specified n limit
** allocate the correct size and return a fresh copy of the string
*/

wchar_t		*ft_wstrndup(const wchar_t *src, size_t n)
{
	wchar_t *dst;

	dst = NULL;
	if (*src)
	{
		dst = (wchar_t *)malloc(sizeof(wchar_t) * (n + 1));
		if (!dst)
			return (NULL);
		dst = ft_wstrncpy(dst, src, n);
	}
	return (dst);
}
