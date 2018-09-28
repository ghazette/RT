/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils2.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/23 23:35:52 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 17:09:53 by rlossy      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

void			free_poly(t_obj *obj)
{
	int i;
	int j;

	i = 0;
	if (obj->npoly > 0)
	{
		while (i < obj->npoly)
		{
			j = 0;
			while (j < obj->poly[i]->ns)
			{
				free(obj->poly[i]->s[j]);
				free(obj->poly[i]->e[j]);
				j++;
			}
			free(obj->poly[i]->s);
			free(obj->poly[i]->e);
			free(obj->poly[i]);
			obj->poly[i] = NULL;
			i++;
		}
		free(obj->poly);
	}
}

static void		reset_next(t_mlx *mlxfree)
{
	int i;

	i = 0;
	if (mlxfree)
	{
		while (i < mlxfree->scene->nb_obj)
		{
			if (mlxfree->scene->objs[i]->texture.data)
				free(mlxfree->scene->objs[i]->texture.data);
			free(mlxfree->scene->objs[i]->name);
			if (mlxfree->scene->objs[i]->type == COMPOSED)
				free_poly(mlxfree->scene->objs[i]);
			free(mlxfree->scene->objs[i]);
			i++;
		}
		free(mlxfree->scene->objs);
		free(mlxfree->scene->interinfo);
		free(mlxfree->scene);
		free(mlxfree);
	}
}

void			reset(t_phong *phong, t_mlx *mlxfree, t_mlx *mlxreset)
{
	if (phong)
	{
		vector3d(&phong->material.color, 0, 0, 0);
		vector3d(&phong->material.specular, 0, 0, 0);
		phong->material.ambient = 0;
		phong->rm_specular = 0;
		phong->is_shadow = 0;
	}
	if (mlxreset)
	{
		mlxreset->i = -1;
		vector3d(&phong->vdir, mlxreset->vdir.x, mlxreset->vdir.y,
					mlxreset->vdir.z);
		vec3_reverse(&phong->vdir);
	}
	reset_next(mlxfree);
}

void			ft_average(t_mlx *mlx, t_vec3 *reg, double coeff)
{
	if (coeff == CONCAT_COLOR)
	{
		RGB.x = ft_reg(RGB.x, 0.0, mlx->reg);
		RGB.y = ft_reg(RGB.y, 0.0, mlx->reg);
		RGB.z = ft_reg(RGB.z, 0.0, mlx->reg);
	}
	else if (coeff == NO_REFLECT)
	{
		RGB.x += ft_reg(reg->x, 0.0, mlx->reg);
		RGB.y += ft_reg(reg->y, 0.0, mlx->reg);
		RGB.z += ft_reg(reg->z, 0.0, mlx->reg);
	}
	else
	{
		RGB.x += ft_reg(reg->x * coeff, 0.0, mlx->reg);
		RGB.y += ft_reg(reg->y * coeff, 0.0, mlx->reg);
		RGB.z += ft_reg(reg->z * coeff, 0.0, mlx->reg);
	}
}
