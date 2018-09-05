/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strstr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:12:16 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 16:15:54 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int j;
	int found;
	int size;

	size = ft_strlen((char*)needle);
	found = 0;
	i = 0;
	if (size == 0)
		return ((char *)haystack);
	while (haystack[i])
	{
		j = i;
		while (haystack[j])
		{
			(haystack[j] == needle[found]) ? found++ : (found = 0);
			j++;
			if (found == size)
				return ((char *)haystack + j - found);
		}
		i++;
	}
	return (NULL);
}
