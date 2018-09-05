/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:06:19 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/31 10:36:59 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdlib.h>

static	int	ft_getintsize(long long n)
{
	int		i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n)
	{
		n /= 10;
		if (n < 0)
			n = -n;
		i++;
	}
	return (i);
}

char		*ft_itoa(long long n)
{
	int			len;
	char		*nbr;
	int			limit;

	limit = 0;
	len = ft_getintsize(n);
	if ((nbr = (char*)malloc(len + 1)) == NULL)
		return (NULL);
	if (n < 0)
	{
		nbr[0] = '-';
		limit = 1;
	}
	nbr[len--] = '\0';
	while (len >= limit)
	{
		if (nbr[len + 1] == '\0' && n < 0)
			nbr[len] = (-(n % 10)) + '0';
		else
			nbr[len] = (n % 10) + '0';
		n /= 10;
		n = (n < 0) ? -n : n;
		len--;
	}
	return (nbr);
}
