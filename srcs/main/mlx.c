/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mlx.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/20 14:49:26 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/17 16:49:44 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

t_mlx			*mlx_init_all(char *window_name)
{
	t_mlx *mlx;

	if (!(mlx = (t_mlx*)malloc(sizeof(t_mlx))))
		return (NULL);
	mlx->mlx = mlx_init();
	if (!(mlx->interf = (t_interface*)malloc(sizeof(t_interface))))
		return (NULL);
	if (!(mlx->win = mlx_new_window(mlx->mlx, WIN_W +
		INTER_WIDTH, WIN_H, window_name)))
		return (NULL);
	if (!(mlx->img = mlx_new_image(mlx->mlx, WIN_W, WIN_H)))
		return (NULL);
	mlx->pixel_img = mlx_get_data_addr(mlx->img,
		&mlx->bpp, &mlx->line, &mlx->ed);
	mlx->line_cnt = 0;
	mlx->aa = 1.0;
	mlx->effect = 0;
	return (mlx);
}

static int		cpy_texture(t_sce *scene, t_sce *src, int i)
{
	size_t	size;
	if (src->objs[i]->texture.data)
	{
		size = (4 * src->objs[i]->texture.width) * src->objs[i]->texture.height;
		if (!(scene->objs[i]->texture.data = malloc(sizeof(char) * size)))
			return (0);
		ft_memcpy(scene->objs[i]->texture.data, src->objs[i]->texture.data, size);
		scene->objs[i]->texture.width = src->objs[i]->texture.width;
		scene->objs[i]->texture.height = src->objs[i]->texture.height;
	}
	else
		scene->objs[i]->texture.data = NULL;
	return (1);
}


static int		obj_cpy(t_sce *scene, t_sce *src)
{
	int	i;

	i = 0;
	if (!(scene->objs = (t_obj**)malloc(sizeof(t_obj*) * scene->nb_obj)))
		return (0);
	while (i < scene->nb_obj)
	{
		scene->objs[i] = (t_obj*)malloc(sizeof(t_obj));
		scene->objs[i]->id = src->objs[i]->id;
		scene->objs[i]->type = src->objs[i]->type;
		if (!(scene->objs[i]->name = ft_strdup(src->objs[i]->name)))
			return (0);
		scene->objs[i]->radius = src->objs[i]->radius;
		scene->objs[i]->poly = src->objs[i]->poly;
		vector3d(&(scene->objs[i]->pos), src->objs[i]->pos.x, src->objs[i]->pos.y, src->objs[i]->pos.z);
		vector3d(&(scene->objs[i]->dir), src->objs[i]->dir.x, src->objs[i]->dir.y, src->objs[i]->dir.z);
		vector3d(&(scene->objs[i]->rot), src->objs[i]->rot.x, src->objs[i]->rot.y, src->objs[i]->rot.z);
		vector3d(&(scene->objs[i]->color), src->objs[i]->color.x, src->objs[i]->color.y, src->objs[i]->color.z);
		scene->objs[i]->material.ambient = src->objs[i]->material.ambient;
		scene->objs[i]->material.reflectivity = src->objs[i]->material.reflectivity;
		vector3d(&(scene->objs[i]->material.color), src->objs[i]->material.color.x, src->objs[i]->material.color.y, src->objs[i]->material.color.z);
		vector3d(&(scene->objs[i]->material.specular), src->objs[i]->material.specular.x, src->objs[i]->material.specular.y, src->objs[i]->material.specular.z);
		scene->objs[i]->render_func = src->objs[i]->render_func;
		if (!(cpy_texture(scene, src, i)))
			return (0);
		i++;
	}
	return (1);
}

static t_sce	*scene_cpy(t_sce *src)
{
	t_sce *scene;

	if (!(scene = (t_sce*)malloc(sizeof(t_sce))))
		return (NULL);
	scene->nb_obj = src->nb_obj;
	if (!(scene->interinfo = malloc(sizeof(t_interinfo))))
		return (NULL);
	scene->nb_spot = src->nb_spot;
	scene->light = src->light;
	scene->cam = src->cam;
	scene->spot = src->spot;
	if (!(obj_cpy(scene, src)))
		return (NULL);
	return (scene);
}

t_mlx			*mlx_cpy(t_mlx *src)
{
	t_mlx *mlx;

	if (!(mlx = (t_mlx*)malloc(sizeof(t_mlx))))
		return (NULL);
	mlx->mlx = src->mlx;
	mlx->win = src->win;
	mlx->img = src->img;
	mlx->pixel_img = src->pixel_img;
	mlx->bpp = src->bpp;
	mlx->line = src->line;
	mlx->ed = src->ed;
	mlx->aa = src->aa;
	mlx->effect = src->effect;
	if (!(mlx->scene = scene_cpy(src->scene)))
		return (NULL);
	return (mlx);
}

void			draw_point(int x, int y, t_mlx *mlx, int color)
{
	int	i;
	int	p;

	i = 0;
	p = (x * ((mlx->bpp / 8)) + y * (mlx->line));
	while (i < (mlx->bpp / 8))
	{
		mlx->pixel_img[p + i] = (char)color;
		color >>= 8;
		i++;
	}
}
