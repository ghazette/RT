/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ray.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/05 17:04:02 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/11 16:22:36 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/rtv1.h"

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

static void		reset(t_phong *phong, t_mlx *mlx, t_rt *rt)
{
	vector3d(&phong->material.color, 0, 0, 0);
	vector3d(&phong->material.specular, 0, 0, 0);
	phong->material.ambient = 0;
	phong->rm_specular = 0;
	phong->fcolor.hex = 0;
	phong->is_shadow = 0;
	if (rt)
	{
		rt->i = -1;
		vector3d(&phong->vdir, rt->vdir.x, rt->vdir.y, rt->vdir.z);
		vec3_reverse(&phong->vdir);
	}
	if (mlx)
	{
		free(mlx->scene->interinfo);
		free(mlx->scene);
		free(mlx);
	}
}

static void		*raytrace(void *mlxp)
{
	t_rt		rt;
	t_phong		phong;

	rt.mlx = (t_mlx*)mlxp;
	rt.savex = rt.mlx->startx - 1;
	while (rt.mlx->starty < rt.mlx->endy)
	{
		rt.mlx->startx = rt.savex;
		while (++rt.mlx->startx < rt.mlx->endx)
		{
			calc_dir_vec(rt.mlx, &rt.vdir, rt.mlx->startx, rt.mlx->starty);
			reset(&phong, NULL, &rt);
			rt.id = intersect(rt.mlx, &rt.mlx->scene->cam->pos, rt.vdir);
			if (rt.id != -1)
				while (++rt.i < rt.mlx->scene->nb_spot)
					light_intersect(rt.mlx, rt.mlx->scene->objs[rt.id]
					, rt.mlx->scene->spot[rt.i], &phong);
			phong_calcfinal(&phong, rt.mlx->scene->nb_spot);
			draw_point(rt.mlx->startx, rt.mlx->starty, rt.mlx,
				phong.fcolor.rgb);
		}
		rt.mlx->starty++;
	}
	reset(&phong, rt.mlx, NULL);
	pthread_exit(NULL);
}

static void		reset_mlx_startend(t_mlx *mlx)
{
	mlx->endy = WIN_H / 2;
	mlx->starty = 0;
	mlx->startx = 0;
	mlx->endx = WIN_W / 4;
}

void			render(t_mlx *mlx)
{
	pthread_t	th[8];
	int			i;

	i = 0;
	reset_mlx_startend(mlx);
	while (mlx->endy <= WIN_H)
	{
		mlx->startx = 0;
		mlx->endx = WIN_W / 4;
		while (mlx->endx <= WIN_W)
		{
			pthread_create(&th[i], NULL, raytrace, mlx_cpy(mlx));
			mlx->startx += WIN_W / 4;
			mlx->endx += WIN_W / 4;
			i++;
		}
		mlx->starty += WIN_H / 2;
		mlx->endy += WIN_H / 2;
	}
	i = -1;
	while (++i < 8)
		pthread_join(th[i], NULL);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}
