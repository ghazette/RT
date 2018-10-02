/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils2.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/23 23:35:52 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/02 16:41:16 by rlossy      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rt.h"

void			free_poly(t_obj *obj)
{
	int i;
	int j;

	i = -1;
	if (obj->npoly > 0)
	{
		while (++i < obj->npoly)
		{
			j = -1;
			while (++j < obj->poly[i]->ns)
			{
				free(obj->poly[i]->s[j]);
				free(obj->poly[i]->e[j]);
			}
			free(obj->poly[i]->s);
			free(obj->poly[i]->e);
			free(obj->poly[i]);
			obj->poly[i] = NULL;
		}
		free(obj->poly);
	}
}

static void		reset_next(t_mlx *mlxfree)
{
	int i;

	i = -1;
	if (mlxfree)
	{
		while (++i < mlxfree->scene->nb_obj)
		{
			if (mlxfree->scene->objs[i]->texture.data)
				free(mlxfree->scene->objs[i]->texture.data);
			free(mlxfree->scene->objs[i]->name);
			if (mlxfree->scene->objs[i]->type == COMPOSED)
				free_poly(mlxfree->scene->objs[i]);
			free(mlxfree->scene->objs[i]);
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

void			ft_calc_edge_normal(t_poly *poly)
{
	t_vec3 v0;
	t_vec3 v1;

	vec3_sub(poly->e[1], poly->e[0], &v0);
	vec3_sub(poly->e[2], poly->e[0], &v1);
	vec3_crossproduct(&v0, &v1, &poly->n);
	vec3_normalize(&poly->n);
}
