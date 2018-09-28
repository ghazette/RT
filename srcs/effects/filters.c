/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   filters.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlossy <rlossy@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/28 17:23:33 by rlossy       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 17:23:33 by rlossy      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

static void			ft_rgb(t_mlx *mlx, int effect)
{
	if (effect == 4)
	{
		RGB.y = 0.0;
		RGB.z = 0.0;
	}
	else if (effect == 5)
	{
		RGB.x = 0.0;
		RGB.z = 0.0;
	}
	else if (effect == 6)
	{
		RGB.x = 0.0;
		RGB.y = 0.0;
	}
}

static void			ft_special_mode(t_mlx *mlx, int effect)
{
	FILTER.gray = RGB.x * 0.299 + RGB.y * 0.587 + RGB.z * 0.114;
	FILTER.sepia[0] = RGB.x * 0.393 + RGB.y * 0.769 + RGB.z * 0.189;
	FILTER.sepia[1] = RGB.x * 0.349 + RGB.y * 0.686 + RGB.z * 0.168;
	FILTER.sepia[2] = RGB.x * 0.272 + RGB.y * 0.534 + RGB.z * 0.131;
	if (effect == 1)
	{
		RGB.x = ft_reg(FILTER.gray, 0.0, mlx->reg);
		RGB.y = ft_reg(FILTER.gray, 0.0, mlx->reg);
		RGB.z = ft_reg(FILTER.gray, 0.0, mlx->reg);
	}
	else if (effect == 2)
	{
		RGB.x = ft_reg(FILTER.sepia[0], 0.0, mlx->reg);
		RGB.y = ft_reg(FILTER.sepia[1], 0.0, mlx->reg);
		RGB.z = ft_reg(FILTER.sepia[2], 0.0, mlx->reg);
	}
	else if (effect == 3)
	{
		RGB.x = mlx->reg - (RGB.x);
		RGB.y = mlx->reg - (RGB.y);
		RGB.z = mlx->reg - (RGB.z);
	}
}

void				ft_effect(t_mlx *mlx, int effect)
{
	if (effect == 1 || effect == 2 || effect == 3)
		ft_special_mode(mlx, effect);
	else if (effect == 4 || effect == 5 || effect == 6)
		ft_rgb(mlx, effect);
}
