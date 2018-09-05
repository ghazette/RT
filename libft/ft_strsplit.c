/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsplit.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:12:11 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 16:15:51 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdlib.h>

static int		wordcount(char *str, char c)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			count++;
			while (str[i] != c && str[i] != '\0')
				i++;
		}
		if (str[i] != '\0')
			i++;
	}
	return (count);
}

static int		wordsize(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	return (i);
}

static void		fill_str(char **ret, const char *str, int size)
{
	int i;

	i = 0;
	(*ret) = (char*)malloc(sizeof(char) * (size + 1));
	while (i < size)
	{
		(*ret)[i] = str[i];
		i++;
	}
	(*ret)[i] = '\0';
}

char			**ft_strsplit(char const *s, char c)
{
	char	**ret;
	int		size;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!s || !c)
		return (NULL);
	size = wordcount((char*)s, c);
	if (!(ret = (char**)malloc(sizeof(char*) * (size + 1))))
		return (NULL);
	ret[size] = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			size = wordsize((char*)s + i, c);
			fill_str(&ret[j++], s + i, size);
			i += size;
		}
		if (s[i] != '\0')
			i++;
	}
	return (ret);
}
