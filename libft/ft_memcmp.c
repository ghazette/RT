/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcmp.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:07:47 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 16:13:33 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_;
	unsigned char	*s2_;

	if (s1 == s2 || n == 0)
		return (0);
	s1_ = (unsigned char *)s1;
	s2_ = (unsigned char *)s2;
	while (n--)
	{
		if (*s1_ != *s2_)
			break ;
		if (n)
		{
			s1_++;
			s2_++;
		}
	}
	return (*s1_ - *s2_);
}
