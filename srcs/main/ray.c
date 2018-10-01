/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ray.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/05 17:04:02 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 16:25:48 by rlossy      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rt.h"

/*
** get the nearest object
** return -1 if no object was found
*/

int				intersect(t_mlx *mlx, t_vec3 *view, t_vec3 vdir)
{
	int				i;
	int				id;
	double			distance;
	double			tmp_distance;
	t_interinfo		interinfo_tmp;

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

static void		ft_aa_next(t_mlx *mlx)
{
	int		it;
	double	coeff;

	it = -1;
	coeff = 1.0;
	while (++it < MAX_ITERATION)
	{
		if (mlx->id == -1)
			break ;
		if (!is_refract(mlx))
			ft_reflect(mlx, &coeff);
		else
			ft_refract(mlx);
	}
	ft_average(mlx, &RGB, CONCAT_COLOR);
	ft_effect(mlx, mlx->effect);
}

static void		ft_aa(t_mlx *mlx, double x, double y)
{
	t_phong	phong;

	mlx->p = 0.0;
	ft_bzero(&mlx->rgb, sizeof(t_vec3));
	while (y < mlx->aay + 1 && (x = mlx->aax) > -1)
	{
		while (x < mlx->aax + 1 && (mlx->p += 1) > 0)
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
	ft_aa_next(mlx);
	draw_point(mlx->aax, mlx->aay, mlx, (((int)(RGB.x / mlx->p * 255) & 0xff)
			<< 16) + (((int)(RGB.y / mlx->p * 255) & 0xff) << 8) +
			((int)(RGB.z / mlx->p * 255) & 0xff));
}

static void		*raytrace(void *mlxp)
{
	double		x;
	double		y;
	t_mlx		*mlx;

	mlx = (t_mlx*)mlxp;
	mlx->reg = 1.0;
	mlx->reg = mlx->aa == 2.0 ? 4.0 : mlx->reg;
	mlx->reg = mlx->aa == 4.0 ? 16.0 : mlx->reg;
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
		return ;
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
