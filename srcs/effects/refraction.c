/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   refraction.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlossy <rlossy@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/28 17:16:04 by rlossy       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 17:29:07 by rlossy      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rt.h"

static void		get_ref_ray(t_mlx *mlx, double n1, double n2)
{
	double	a;
	double	b;
	double	c;
	double	n;

	a = vec3_dotproduct(&mlx->vdir, &mlx->scene->interinfo->normal);
	if (a < 0.0)
		a = -a;
	n = n1 / n2;
	b = n * n * (1.0 - (a * a));
	c = sqrt(1.0 - b);
	vec3_scale(&mlx->vdir, n, MULT, &mlx->vdir);
	vec3_scale(&mlx->scene->interinfo->normal, (n * a - c), MULT,
				&mlx->scene->interinfo->normal);
	vec3_add(&mlx->vdir, &mlx->scene->interinfo->normal, &mlx->vdir);
	vec3_normalize(&mlx->vdir);
}

int				is_refract(t_mlx *mlx)
{
	double	mag;
	t_vec3	tmp;

	if (mlx->scene->objs[mlx->id]->material.refraction <= 0.0)
		return (0);
	vec3_crossproduct(&mlx->vdir, &mlx->scene->interinfo->normal, &tmp);
	mag = vec3_magnitude(&tmp);
	return ((((AIR / mlx->scene->objs[mlx->id]->material.refraction)
				* mag) < 1));
}

void			view_correction(t_mlx *mlx, t_vec3 *view, int type)
{
	t_vec3 tmp;

	vec3_cpy(view, &mlx->scene->interinfo->intersect);
	vec3_scale(&mlx->vdir, 0.01, MULT, &tmp);
	if (type == REFRACT)
		vec3_add(view, &tmp, view);
	else
		vec3_sub(view, &tmp, view);
}

void			ft_refract(t_mlx *mlx)
{
	int		id;
	t_vec3	view;
	t_phong	phong;

	if (mlx->id == -1 || mlx->scene->objs[mlx->id]->material.refraction <= 0.0)
		return ;
	reset(&phong, NULL, mlx);
	get_ref_ray(mlx, AIR, mlx->scene->objs[mlx->id]->material.refraction);
	view_correction(mlx, &view, REFRACT);
	id = intersect(mlx, &view, mlx->vdir);
	if (mlx->id == id)
	{
		vec3_reverse(&mlx->scene->interinfo->normal);
		get_ref_ray(mlx, mlx->scene->objs[mlx->id]->material.refraction, AIR);
		view_correction(mlx, &view, REFRACT);
	}
	mlx->id = intersect(mlx, &view, mlx->vdir);
	if (mlx->id != -1)
		while (++mlx->i < mlx->scene->nb_spot)
			light_intersect(mlx, mlx->scene->objs[mlx->id]
					, mlx->scene->spot[mlx->i], &phong);
	if (mlx->id == -1)
		return ;
	phong_calcfinal(&phong, mlx->scene->nb_spot);
	ft_average(mlx, &(phong.material.color), NO_REFLECT);
}
