/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa_base.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:06:25 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/31 10:36:00 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdlib.h>

static	int	getsize(long long nb, int base)
{
	int				i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb /= base;
		if (nb < 0)
			nb = -nb;
		i++;
	}
	return (i);
}

char		*ft_itoa_base(long long nbr, int base)
{
	char			*ret;
	int				size;
	char			tab[37];

	if (base == 10)
		return (ft_itoa(nbr));
	ft_strcpy(tab, "0123456789abcdefghijklmnopqrstuvwxyz");
	size = getsize(nbr, base);
	if ((ret = (char*)malloc(sizeof(char) + (size + 1))) == NULL)
		return (NULL);
	if (nbr == 0)
		ret[0] = '0';
	ret[size--] = '\0';
	while (nbr != 0)
	{
		if (ret[size + 1] == '\0' && nbr < 0)
			ret[size] = tab[-(nbr % base)];
		else
			ret[size] = tab[nbr % base];
		nbr /= base;
		if (nbr < 0)
			nbr = -nbr;
		size--;
	}
	return (ret);
}
