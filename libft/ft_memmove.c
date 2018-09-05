/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memmove.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:08:10 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 16:16:44 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	char				*dst_ptr;
	char				*src_tmp;
	const char			*src_ptr;

	i = 0;
	src_ptr = (const char *)src;
	dst_ptr = (char *)dst;
	src_tmp = (char *)malloc(sizeof(char) * len);
	if (src_tmp == NULL)
		return (dst);
	while (i < len)
	{
		src_tmp[i] = src_ptr[i];
		i++;
	}
	i = 0;
	while (i < len)
	{
		dst_ptr[i] = src_tmp[i];
		i++;
	}
	free(src_tmp);
	return (dst);
}
