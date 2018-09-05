/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_atoi.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:05:06 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/11 16:21:28 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

long long int		ft_atoi(const char *str)
{
	int				i;
	int				neg;
	long long int	ret;

	ret = 0;
	neg = 1;
	i = 0;
	if (str)
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		neg = (str[i] == '-') ? -1 : 1;
		i += (str[i] == '-' || str[i] == '+') ? 1 : 0;
		while (str[i] && ft_isdigit(str[i]))
		{
			ret *= 10;
			ret += str[i] - '0';
			i++;
		}
	}
	return (ret * neg);
}
