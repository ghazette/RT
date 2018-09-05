/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strtrim.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:12:32 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 16:16:01 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s)
{
	int		i;
	int		len;
	char	*str;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	while (ft_isspace(s[len - 1]))
		len--;
	i = -1;
	while (ft_isspace(s[++i]))
		len--;
	if (len < 0)
		len = 0;
	if ((str = (char*)malloc(sizeof(*str) * len + 1)) == NULL)
		return (NULL);
	ft_strncpy(str, s + i, len);
	str[len] = '\0';
	return (str);
}
