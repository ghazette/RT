/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_newcstr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/12 11:30:01 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/31 09:52:21 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

char		*ft_newcstr(int c, size_t size)
{
	char *str;

	if (!(str = ft_strnew(size)))
		return (NULL);
	str = ft_memset(str, c, size);
	return (str);
}
