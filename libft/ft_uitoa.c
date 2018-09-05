/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_uitoa.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/04 15:01:43 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/31 11:36:56 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdlib.h>

static	int	ft_getintsize(unsigned long long n)
{
	int		i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char		*ft_uitoa(unsigned long long n)
{
	int			len;
	char		*nbr;
	int			limit;

	limit = 0;
	len = ft_getintsize(n);
	if (!(nbr = ft_strnew(len)))
		return (NULL);
	nbr[len--] = '\0';
	while (len >= limit)
	{
		nbr[len] = (n % 10) + '0';
		n /= 10;
		len--;
	}
	return (nbr);
}
