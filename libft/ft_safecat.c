/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_safecat.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/19 10:26:32 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/19 10:37:01 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdlib.h>

char	*ft_safecat(char *dest, const char *src)
{
	char *tmp;

	if (!(tmp = ft_strjoin(dest, src)))
		return (NULL);
	ft_strdel(&dest);
	return (tmp);
}
