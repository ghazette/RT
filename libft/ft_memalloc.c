/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memalloc.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:07:25 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 16:13:24 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	unsigned char	*mem;
	size_t			i;

	if ((mem = malloc(size)) == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		mem[i] = '\0';
		i++;
	}
	return (mem);
}
