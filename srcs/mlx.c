/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mlx.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/20 14:49:26 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/10 10:29:44 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/rtv1.h"

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
	return (mlx);
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
	scene->objs = src->objs;
	scene->cam = src->cam;
	scene->spot = src->spot;
	int i = 0;
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
	if (!(mlx->scene = scene_cpy(src->scene)))
		return (NULL);
	mlx->starty = src->starty;
	mlx->startx = src->startx;
	mlx->endx = src->endx;
	mlx->endy = src->endy;
	return (mlx);
}

static int		conv_coord(int x, int y, t_mlx *mlx)
{
	return ((x * ((mlx->bpp) / 8)) + (y * mlx->line));
}

void			draw_point(int x, int y, t_mlx *mlx, unsigned char *color)
{
	int pixel_pos;

	pixel_pos = conv_coord(x, y, mlx);
	if (pixel_pos < (WIN_W * WIN_H * (mlx->bpp / 8)) && pixel_pos >= 0)
	{
		if (color != 0)
		{
			mlx->pixel_img[pixel_pos] = (char)color[0];
			mlx->pixel_img[pixel_pos + 1] = (char)color[1];
			mlx->pixel_img[pixel_pos + 2] = (char)color[2];
		}
		else
		{
			mlx->pixel_img[pixel_pos] = (char)0;
			mlx->pixel_img[pixel_pos + 1] = (char)0;
			mlx->pixel_img[pixel_pos + 2] = (char)0;
		}
	}
}
