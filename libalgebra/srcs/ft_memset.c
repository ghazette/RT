/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memset.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/30 10:05:36 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/06 15:33:39 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/libalgebra.h"

void	*ft_memset(void *b, int c, size_t n)
{
	unsigned char *b_;

	b_ = (unsigned char *)b;
	if (n == 0)
		return (b);
	while (n--)
	{
		*b_ = (unsigned char)c;
		b_++;
	}
	return (b);
}
