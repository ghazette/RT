/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_splitwhitespace.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mkulhand <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/28 10:03:37 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 10:03:40 by mkulhand    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

static int		is_white(char c)
{
	if (c == ' ' || c == '	')
		return (1);
	return (0);
}

static int		wordcount(char *str)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (!is_white(str[i]))
		{
			count++;
			while (!is_white(str[i]) && str[i] != '\0')
				i++;
		}
		if (str[i] != '\0')
			i++;
	}
	return (count);
}

static int		wordsize(char *str)
{
	int i;

	i = 0;
	while (!is_white(str[i]) && str[i] != '\0')
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

char			**ft_splitwhitespace(char const *s)
{
	char	**ret;
	int		size;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!s)
		return (NULL);
	size = wordcount((char*)s);
	if (!(ret = (char**)malloc(sizeof(char*) * (size + 1))))
		return (NULL);
	ret[size] = 0;
	while (s[i])
	{
		if (!is_white(s[i]))
		{
			size = wordsize((char*)s + i);
			fill_str(&ret[j++], s + i, size);
			i += size;
		}
		if (s[i] != '\0')
			i++;
	}
	return (ret);
}