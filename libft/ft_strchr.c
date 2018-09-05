/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strchr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:09:35 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 16:14:18 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	char *s2;
	char c2;

	c2 = (char)c;
	s2 = (char*)s;
	while (*s2 != '\0')
	{
		if (*s2 == c2)
			return (s2);
		s2++;
	}
	if (*s2 == c2)
		return (s2);
	return (NULL);
}
