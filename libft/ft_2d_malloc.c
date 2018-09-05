/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_2d_malloc.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/24 11:32:01 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2017/11/24 11:32:37 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>

char	**ft_2d_malloc(int width, int height)
{
	char **ret;

	if (!(ret = (char**)malloc(sizeof(char*) * height)))
		return (NULL);
	height--;
	ret[height] = 0;
	height--;
	while (height >= 0)
	{
		if (!(ret[height] = (char*)malloc(sizeof(char) * width)))
			return (NULL);
		height--;
	}
	return (ret);
}
