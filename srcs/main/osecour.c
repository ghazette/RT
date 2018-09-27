/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   osecour.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/05 17:04:02 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/26 15:14:13 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

/*
** get the nearest object
** return -1 if no object was found
*/

static int		intersect(t_mlx *mlx, t_vec3 *view, t_vec3 vdir)
{
	t_interinfo		interinfo_tmp;
	int				i;
	double			distance;
	double			tmp_distance;
	int				id;

	i = 0;
	id = -1;
	distance = 9999999;
	while (i < mlx->scene->nb_obj)
	{
		if ((mlx->scene->objs[i]->render_func(&interinfo_tmp, view,
			mlx->scene->objs[i], vdir)))
		{
			tmp_distance = vec3_length(&interinfo_tmp.intersect, view);
			if (tmp_distance < distance)
			{
				inter_cpy(mlx->scene->interinfo, &interinfo_tmp);
				distance = tmp_distance;
				id = i;
			}
		}
		i++;
	}
	return (id);
}

static void		reset(t_phong *phong, t_mlx *mlxfree, t_mlx *mlxreset)
{
	int i;

	i = 0;
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
		vector3d(&phong->vdir, mlxreset->vdir.x, mlxreset->vdir.y, mlxreset->vdir.z);
		vec3_reverse(&phong->vdir);
	}
	if (mlxfree)
	{
		while (i < mlxfree->scene->nb_obj)
		{
			if (mlxfree->scene->objs[i]->texture.data)
				free(mlxfree->scene->objs[i]->texture.data);
			free(mlxfree->scene->objs[i]->name);
			free(mlxfree->scene->objs[i]);
			i++;
		}
		free(mlxfree->scene->objs);
		free(mlxfree->scene->interinfo);
		free(mlxfree->scene);
		free(mlxfree);
	}
}

static void		ft_average(t_mlx *mlx, t_vec3 *reg, double coeff)
{
	if (coeff == CONCAT_COLOR)
	{
		RGB.x = ft_reg(RGB.x, 0.0, mlx->reg);
		RGB.y = ft_reg(RGB.y, 0.0, mlx->reg);
		RGB.z = ft_reg(RGB.z, 0.0, mlx->reg);
		return;
	}
	else if (coeff == NO_REFLECT)
	{
		RGB.x += ft_reg(reg->x, 0.0, mlx->reg);
		RGB.y += ft_reg(reg->y, 0.0, mlx->reg);
		RGB.z += ft_reg(reg->z, 0.0, mlx->reg);
	}
	else if (coeff == REFRACT)
	{
		RGB.x += ft_reg(reg->x, 0.0, mlx->reg);
		RGB.y += ft_reg(reg->y, 0.0, mlx->reg);
		RGB.z += ft_reg(reg->z, 0.0, mlx->reg);
	}
	else
	{
		RGB.x += ft_reg(reg->x * coeff / mlx->aa, 0.0, mlx->reg);
		RGB.y += ft_reg(reg->y * coeff / mlx->aa, 0.0, mlx->reg);
		RGB.z += ft_reg(reg->z * coeff / mlx->aa, 0.0, mlx->reg);
	}
}

static void		get_refracted_ray(t_mlx *mlx, double n1, double n2)
{
	double	top;
	double 	down;
	double	refracted_angle;
	t_vec3	tmp;

	top = vec3_dotproduct(&mlx->vdir, &mlx->scene->interinfo->normal);
	down = vec3_magnitude(&mlx->vdir) * vec3_magnitude(&mlx->scene->interinfo->normal);
	refracted_angle = acos(top / down);
	refracted_angle = asin(n1 * sin(refracted_angle) / n2);
	vec3_scale(&mlx->scene->interinfo->normal, refracted_angle, MULT, &tmp);
	vec3_add(&mlx->vdir, &tmp, &mlx->vdir);
	vec3_normalize(&mlx->vdir);
}

static int		is_refract(t_mlx *mlx)
{
	t_vec3 	tmp;
	double	mag;

	vec3_crossproduct(&mlx->vdir, &mlx->scene->interinfo->normal, &tmp);
	mag = vec3_magnitude(&tmp);
	return ((((REFRACT_AIR / mlx->scene->objs[mlx->id]->material.refraction) * mag) < 1));
}

static void		view_correction(t_mlx *mlx, t_vec3 *view)
{
	t_vec3 tmp;

	vec3_cpy(view, &mlx->scene->interinfo->intersect);
	vec3_scale(&mlx->vdir, 0.01, MULT, &tmp);
	vec3_add(view, &tmp, view);
}

static void		ft_refract(t_mlx *mlx)
{
	int		it = 0;
	int		id;
	t_phong	phong;
	t_vec3 	view;

	/*while (it < MAX_ITERATION)
	{*/
		if (mlx->id == -1 || mlx->scene->objs[mlx->id]->material.refraction <= 0.0)
			return;
		reset(&phong, NULL, mlx);
		view_correction(mlx, &view);
		get_refracted_ray(mlx, REFRACT_AIR, mlx->scene->objs[mlx->id]->material.refraction);
		id = intersect(mlx, &view, mlx->vdir);
		if (mlx->id == id)
		{
			vec3_reverse(&mlx->scene->interinfo->normal);
			get_refracted_ray(mlx, mlx->scene->objs[mlx->id]->material.refraction, REFRACT_AIR);
			view_correction(mlx, &view);
		}
		mlx->id = intersect(mlx, &view, mlx->vdir);
		if (mlx->id != -1)
			while (++mlx->i < mlx->scene->nb_spot)
				light_intersect(mlx, mlx->scene->objs[mlx->id]
				, mlx->scene->spot[mlx->i], &phong);
		if (mlx->id == -1)
			return;
		phong_calcfinal(&phong, mlx->scene->nb_spot);
		ft_average(mlx, &(phong.material.color), REFRACT);
		it++;
	//}
}

static void		get_reflected_ray(t_mlx *mlx)
{
	double reflet;
	t_vec3 tmp;

	reflet = 2.0 * vec3_dotproduct(&mlx->vdir, &mlx->scene->interinfo->normal);
	vec3_scale(&mlx->scene->interinfo->normal, reflet, MULT, &tmp);
	vec3_sub(&mlx->vdir, &tmp, &mlx->vdir);
	vec3_normalize(&mlx->vdir);
}

static void		ft_reflect(t_mlx *mlx, double *coeff)
{
	t_phong	phong;
	t_vec3 	view;

	if (mlx->id != -1 && mlx->scene->objs[mlx->id]->material.reflectivity > 0.0)
	{
		*coeff *= mlx->scene->objs[mlx->id]->material.reflectivity;
		get_reflected_ray(mlx);
		view_correction(mlx, &view);
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

static void		ft_aa(t_mlx *mlx, double x, double y)
{
	double	p;
	double	coeff;
	t_phong	phong;
	int		it;

	it = 0;
	p = 0.0;
	coeff = 1;
	ft_bzero(&mlx->rgb, sizeof(t_vec3));
	while (y < mlx->aay + 1 && (x = mlx->aax) > -1)
	{
		while (x < mlx->aax + 1 && (p += 1) > 0)
		{
			calc_dir_vec(mlx, &mlx->vdir, x, y);
			reset(&phong, NULL, mlx);
			mlx->id = intersect(mlx, &mlx->scene->cam->pos, mlx->vdir);
			if (mlx->id != -1)
				while (++mlx->i < mlx->scene->nb_spot)
					light_intersect(mlx, mlx->scene->objs[mlx->id]
					, mlx->scene->spot[mlx->i], &phong);
			phong_calcfinal(&phong, mlx->scene->nb_spot);
			ft_average(mlx, &phong.material.color, NO_REFLECT);
			x += (1.0 / mlx->aa);
		}
		y = y + (1.0 / mlx->aa);
	}
	y -= mlx->aa;
	x -= mlx->aa;
	while (it < MAX_ITERATION)
	{
		if (!is_refract(mlx))
			ft_reflect(mlx, &coeff);
		else
			ft_refract(mlx);
		it++;
	}
	ft_average(mlx, &RGB, CONCAT_COLOR);
	ft_effect(mlx, mlx->effect);
	draw_point(mlx->aax, mlx->aay, mlx, (((int)(RGB.x / p * 255) & 0xff)
			<< 16) + (((int)(RGB.y / p * 255) & 0xff) << 8) +
			((int)(RGB.z / p * 255) & 0xff));
}

static void		*raytrace(void *mlxp)
{
	t_mlx		*mlx;
	double		x;
	double 		y;

	mlx = (t_mlx*)mlxp;
	if (mlx->aa == 2.0)
		mlx->reg = 4.0;
	else if (mlx->aa == 4.0)
		mlx->reg = 16.0;
	else
		mlx->reg = 1.0;
	y = 0.0;
	while (y < WIN_H)
	{
		x = WIN_W * mlx->th / THREADS;
		while (x < WIN_W * (mlx->th + 1) / THREADS)
		{
			mlx->aax = (int)x;
			mlx->aay = (int)y;
			ft_aa(mlx, x, y);
			x++;
		}
		y++;
	}
	reset(NULL, mlx, NULL);
	pthread_exit(NULL);
}

void			render(t_mlx *mlx)
{
	int			i;
	t_mlx		**p;
	pthread_t	th[THREADS];

	i = -1;
	if (!(p = (t_mlx**)malloc(sizeof(t_mlx*) * THREADS)))
		return;
	while (++i < THREADS)
	{
		p[i] = mlx_cpy(mlx);
		p[i]->th = i;
		pthread_create(&th[i], NULL, raytrace, p[i]);
	}
	i = -1;
	while (++i < THREADS)
		pthread_join(th[i], NULL);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}
