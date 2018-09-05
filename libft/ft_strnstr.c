/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnstr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:12:01 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 16:15:45 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	int i;
	int j;
	int found;
	int size;

	size = ft_strlen((char*)s2);
	found = 0;
	i = -1;
	if (size == 0)
		return ((char *)s1);
	while (s1[++i] != '\0' && len)
	{
		j = i;
		while (s1[j] == s2[found] && len && s1[i] != '\0' && s2[found] != '\0')
		{
			len--;
			j++;
			found++;
		}
		len += found - 1;
		if (found == size)
			return ((char *)s1 + i);
		found = 0;
	}
	return (NULL);
}
