/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   light.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/06 16:24:31 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/06 15:09:48 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static int	is_light_blocked(t_mlx *mlx, t_vec3 *view, t_vec3 vdir, int id)
{
	int				i;
	double			len;
	double			tmplen;
	int				lightblocked;
	t_interinfo		inter_tmp;

	i = 0;
	lightblocked = 0;
	len = vec3_length(&mlx->scene->interinfo->intersect, view);
	while (i < mlx->scene->nb_obj)
	{
		if (id != mlx->scene->objs[i]->id && (mlx->scene->objs[i]->render_func(
			&inter_tmp, view, mlx->scene->objs[i], vdir)))
		{
			tmplen = vec3_length(&inter_tmp.intersect, view);
			if (tmplen - 0.0001 < len)
				lightblocked = 1;
		}
		i++;
	}
	return (lightblocked);
}

void		light_intersect(t_mlx *mlx, t_obj *obj, t_spot *spot,
	t_phong *phong)
{
	t_vec3		light_vec;

	if (mlx->scene->light)
	{
		vec3_sub(&mlx->scene->interinfo->intersect, &spot->pos, &light_vec);
		vec3_normalize(&light_vec);
		if ((is_light_blocked(mlx, &spot->pos, light_vec, obj->id)))
		{
			phong->is_shadow = 1;
			phong->rm_specular = 1;
		}
		vec3_reverse(&light_vec);
		phong->normal = &mlx->scene->interinfo->normal;
		phong->light_vec = &light_vec;
		phong->spot = spot;
		phong->obj = obj;
		phong_calc(phong);
	}
}
