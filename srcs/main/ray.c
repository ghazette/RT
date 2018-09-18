/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ray.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/05 17:04:02 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/18 15:53:58 by ghazette    ###    #+. /#+    ###.fr     */
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

static void		ft_aa(t_mlx *mlx, double x, double y)
{
	int it = 0;
	int it2 = 10;
	double	p;
	t_phong	phong;
	t_vec3 tmpview;
	double reflet;
	double	coeff = 1;
	p = 0.0;
	reflet = 0;
	ft_bzero(&mlx->rgb, sizeof(t_vec3));
	while (it < it2)
	{
		if (it == 0)
			vec3_cpy(&tmpview, &mlx->scene->cam->pos);
		while (y < mlx->aay + 1 && (x = mlx->aax) > -1)
		{
			while (x < mlx->aax + 1 && (p += 1) > 0)
			{
				if (it == 0)
					calc_dir_vec(mlx, &mlx->vdir, x, y);
				reset(&phong, NULL, mlx);
				mlx->id = intersect(mlx, &tmpview, mlx->vdir);
				if (mlx->id != -1)
					while (++mlx->i < mlx->scene->nb_spot)
						light_intersect(mlx, mlx->scene->objs[mlx->id]
						, mlx->scene->spot[mlx->i], &phong);
				if (mlx->id  == -1)
					break;
				phong_calcfinal(&phong, mlx->scene->nb_spot);
				if (it == 0)
				{
					mlx->rgb.x += ft_reg(phong.material.color.x, 0.0, 4.0);
					mlx->rgb.y += ft_reg(phong.material.color.y, 0.0, 4.0);
					mlx->rgb.z += ft_reg(phong.material.color.z, 0.0, 4.0);
				}
				else
				{
					mlx->rgb.x += ft_reg(phong.material.color.x * coeff / 1.5, 0.0, 4.0);
					mlx->rgb.y += ft_reg(phong.material.color.y * coeff / 1.5, 0.0, 4.0);
					mlx->rgb.z += ft_reg(phong.material.color.z * coeff / 1.5, 0.0, 4.0);
				}
				x += (1.0 / mlx->aa);
			}
			y = y + (1.0 / mlx->aa);
		}
		if (mlx->id != -1)
			coeff *= mlx->scene->objs[mlx->id]->material.reflectivity;
		if (mlx->id  == -1)
			break ;
		reflet = 2.0 * vec3_dotproduct(&mlx->vdir, &mlx->scene->interinfo->normal);
		vec3_cpy(&tmpview, vec3_sub(&mlx->scene->interinfo->intersect, &mlx->vdir, &mlx->scene->interinfo->intersect));
		t_vec3 test;
		vec3_scale(&mlx->scene->interinfo->normal, reflet, MULT, &test);
		vec3_sub(&mlx->vdir, &test, &mlx->vdir);
		it++;
		y -= mlx->aa;
		x -= mlx->aa;
		if (it != it2)
			p = 0;
	}
	mlx->rgb.x = ft_reg(mlx->rgb.x, 0.0, 4.0);
	mlx->rgb.y = ft_reg(mlx->rgb.y, 0.0, 4.0);
	mlx->rgb.z = ft_reg(mlx->rgb.z, 0.0, 4.0);
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
