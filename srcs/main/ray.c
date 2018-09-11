/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ray.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/05 17:04:02 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/11 10:08:44 by ghazette    ###    #+. /#+    ###.fr     */
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

static void		reset(t_phong *phong, t_mlx *mlx, t_mlx *mlxp)
{
	int i;

	i = 0;
	vector3d(&phong->material.color, 0, 0, 0);
	vector3d(&phong->material.specular, 0, 0, 0);
	phong->material.ambient = 0;
	phong->rm_specular = 0;
	phong->fcolor.hex = 0;
	phong->is_shadow = 0;
	if (mlxp)
	{
		mlxp->i = -1;
		vector3d(&phong->vdir, mlxp->vdir.x, mlxp->vdir.y, mlxp->vdir.z);
		vec3_reverse(&phong->vdir);
	}
	if (mlx)
	{
		while (i < mlx->scene->nb_obj)
		{
			free(mlx->scene->objs[i]->texture.data);
			free(mlx->scene->objs[i]->name);
			free(mlx->scene->objs[i]);
			i++;
		}
		free(mlx->scene->objs);
		free(mlx->scene->interinfo);
		free(mlx->scene);
		free(mlx);
	}
}

static void		ft_aa(t_mlx *mlx, double x, double y)
{
	double	p;
	t_phong		phong;

	p = 0.0;
	ft_bzero(&mlx->rgb, sizeof(t_vec3));
	mlx->aa = 1.0;
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
			mlx->rgb.x += ft_reg(phong.material.color.x, 0.0, 1.0);
			mlx->rgb.y += ft_reg(phong.material.color.y, 0.0, 1.0);
			mlx->rgb.z += ft_reg(phong.material.color.z, 0.0, 1.0);
			x += (1.0 / mlx->aa);
		}
		y = y + (1.0 / mlx->aa);
	}
	draw_point(mlx->aax, mlx->aay, mlx, (((int)(mlx->rgb.x / p * 255) & 0xff)
			<< 16) + (((int)(mlx->rgb.y / p * 255) & 0xff) << 8) +
			((int)(mlx->rgb.z / p * 255) & 0xff));
}

static void		*raytrace(void *mlxp)
{
	t_mlx		*mlx;
	double		x;
	double 		y;

	mlx = (t_mlx*)mlxp;
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
	pthread_exit(NULL);
}

void			render(t_mlx *mlx)
{
	int			i;
	t_mlx		p[THREADS];
	pthread_t	th[THREADS];

	i = -1;
	while (++i < THREADS)
	{
		p[i] = *mlx_cpy(mlx);
		p[i].th = i;
		pthread_create(&th[i], NULL, raytrace, &p[i]);
	}
	i = -1;
	while (++i < THREADS)
		pthread_join(th[i], NULL);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}