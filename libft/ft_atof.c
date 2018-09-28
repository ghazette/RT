/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_atof.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mkulhand <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/11 12:41:47 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/19 12:32:51 by rlossy      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

static double	ft_atof_next(int i, char *const *split, double ret, double expo)
{
	while (split[1][i])
	{
		ret += (double)(split[1][i] - '0') / expo;
		i++;
		expo *= 10;
	}
	return (ret);
}

double			ft_atof(const char *str)
{
	int		i;
	int		neg;
	char	**split;
	double	ret;
	double	expo;

	if ((split = ft_strsplit(str, '.')) != NULL)
	{
		ret = ft_atoi(split[0]);
		neg = (split[0][0] == '-') ? 1 : 0;
		ret = (ret < 0) ? -ret : ret;
		i = 0;
		expo = 10;
		if (!split[1])
		{
			ft_free2d(&split);
			return (ret);
		}
		ret = ft_atof_next(i, split, ret, expo);
		ret = (neg) ? -ret : ret;
		ft_free2d(&split);
		return (ret);
	}
	return (0);
}
