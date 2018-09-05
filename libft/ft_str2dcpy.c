/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_str2dcpy.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/30 20:51:45 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 16:14:11 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_str2dcpy(char **dst, char src, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (dst && src)
	{
		while (dst[i] != 0)
		{
			j = 0;
			while (j < n)
			{
				dst[i][j] = src;
				j++;
			}
			dst[i][j] = '\0';
			i++;
		}
	}
}
