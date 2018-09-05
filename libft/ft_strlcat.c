/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strlcat.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:10:49 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 16:15:01 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t dst_len;
	size_t src_len;
	size_t i;
	size_t j;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	dst_len = (size < dst_len) ? size : dst_len;
	i = dst_len;
	j = 0;
	if (size <= dst_len)
		return (src_len + size);
	while (i < size - 1 && src[j] != '\0')
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (dst_len + src_len);
}
