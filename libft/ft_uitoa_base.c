/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_uitoa_base.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/04 15:16:04 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/31 11:38:25 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdlib.h>

static	int	getsize(unsigned long long nb, int base)
{
	int		i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb)
	{
		nb /= base;
		i++;
	}
	return (i);
}

char		*ft_uitoa_base(unsigned long long nbr, int base)
{
	char			*ret;
	int				size;
	char			tab[37];

	if (base == 10)
		return (ft_uitoa(nbr));
	ft_strcpy(tab, "0123456789abcdefghijklmnopqrstuvwxyz");
	size = getsize(nbr, base);
	if (!(ret = ft_strnew(size)))
		return (NULL);
	if (nbr == 0)
		ret[0] = '0';
	ret[size--] = '\0';
	while (nbr != 0)
	{
		ret[size] = tab[nbr % base];
		nbr /= base;
		size--;
	}
	return (ret);
}
