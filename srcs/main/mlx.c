/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mlx.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/20 14:49:26 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 15:40:44 by rlossy      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rt.h"

t_mlx			*mlx_init_all(char *window_name)
{
	t_mlx *mlx;

	if (!(mlx = (t_mlx*)malloc(sizeof(t_mlx))))
		return (NULL);
	mlx->mlx = mlx_init();
	if (!(mlx->interf = malloc(sizeof(t_interface))))
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
	mlx->ambient = 0.1;
	mlx->aaoff = 0;
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
