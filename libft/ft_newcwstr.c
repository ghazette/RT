/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_newcwstr.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/12 11:29:24 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/31 10:30:27 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdlib.h>

wchar_t		*ft_newcwstr(int c, size_t size)
{
	wchar_t *str;
	size_t	i;

	i = 0;
	if (!(str = (wchar_t*)malloc(sizeof(wchar_t) * (size + 1))))
		return (NULL);
	while (i < size)
		str[i++] = c;
	str[i] = L'\0';
	return (str);
}
