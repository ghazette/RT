/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_free3d.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/04 07:45:03 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 16:11:42 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdlib.h>

void	ft_free3d(char ****str)
{
	int i;

	i = 0;
	while ((*str)[i] != 0)
	{
		ft_free2d(&((*str)[i]));
		i++;
	}
	free((*str)[i]);
	free(*str);
	*str = NULL;
}
