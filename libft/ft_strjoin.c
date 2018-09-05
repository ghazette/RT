/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjoin.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:10:40 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 16:14:44 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdlib.h>

static void	fill_str(int *index, char **out, char const *in, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		(*out)[*index] = in[i];
		(*index)++;
		i++;
	}
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len[3];
	int		index;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	index = 0;
	len[0] = ft_strlen(s1);
	len[1] = ft_strlen(s2);
	len[2] = len[0] + len[1];
	if ((str = (char*)malloc(sizeof(char) * len[2] + 1)) == NULL)
		return (NULL);
	fill_str(&index, &str, s1, len[0]);
	fill_str(&index, &str, s2, len[1]);
	str[index] = '\0';
	return (str);
}
