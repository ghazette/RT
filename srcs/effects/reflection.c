/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   reflection.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlossy <rlossy@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/28 17:15:42 by rlossy       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 17:15:42 by rlossy      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

static void		get_reflected_ray(t_mlx *mlx)
{
	double reflet;
	t_vec3 tmp;

	reflet = 2.0 * vec3_dotproduct(&mlx->vdir, &mlx->scene->interinfo->normal);
	vec3_scale(&mlx->scene->interinfo->normal, reflet, MULT, &tmp);
	vec3_sub(&mlx->vdir, &tmp, &mlx->vdir);
	vec3_normalize(&mlx->vdir);
}

void			ft_reflect(t_mlx *mlx, double *coeff)
{
	t_vec3	view;
	t_phong	phong;

	if (mlx->id != -1 && mlx->scene->objs[mlx->id]->material.reflectivity > 0.0)
	{
		*coeff *= mlx->scene->objs[mlx->id]->material.reflectivity;
		view_correction(mlx, &view, 0);
		get_reflected_ray(mlx);
		reset(&phong, NULL, mlx);
		mlx->id = intersect(mlx, &view, mlx->vdir);
		if (mlx->id != -1)
			while (++mlx->i < mlx->scene->nb_spot)
				light_intersect(mlx, mlx->scene->objs[mlx->id]
						, mlx->scene->spot[mlx->i], &phong);
		if (mlx->id == -1)
			return ;
		phong_calcfinal(&phong, mlx->scene->nb_spot);
		ft_average(mlx, &phong.material.color, *coeff);
	}
}
