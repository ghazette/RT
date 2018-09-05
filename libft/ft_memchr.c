/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memchr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:07:42 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 16:13:31 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int				i;
	unsigned char	*s_;

	s_ = (unsigned char *)s;
	i = 0;
	while (n--)
	{
		if (s_[i] == ((unsigned char)c))
			return (&(s_[i]));
		i++;
	}
	return (NULL);
}
