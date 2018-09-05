/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_realloc.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/13 14:25:32 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 16:14:06 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdlib.h>

void	*ft_realloc(void *ptr, size_t new_size)
{
	char	*newptr;

	if (!new_size && ptr)
	{
		if (!(newptr = (char *)malloc(1)))
			return (NULL);
		ft_memdel(&ptr);
		return (newptr);
	}
	if (!(newptr = (char *)malloc(new_size)))
		return (NULL);
	if (ptr)
	{
		ft_memcpy(newptr, ptr, new_size);
		ft_memdel(&ptr);
	}
	return (newptr);
}
