/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   key_input.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/20 15:31:37 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/12 11:05:03 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

static void	key_minus(t_mlx *mlx)
{
	if (!mlx->interf->focus)
	{
		if (mlx->interf->id_select_obj != -1)
		{
			if (mlx->interf->id_select_obj < mlx->scene->nb_obj)
				mlx->scene->objs[mlx->interf->id_select_obj]->pos.z--;
			else
				mlx->scene->spot[mlx->interf->id_select_obj -
					mlx->scene->nb_obj]->pos.z--;
		}
		else
		{
			mlx->scene->cam->pos.z -= 5;
			init_camera(mlx);
		}
		render(mlx);
	}
}

static void	key_plus(t_mlx *mlx)
{
	if (!mlx->interf->focus)
	{
		if (mlx->interf->id_select_obj != -1)
		{
			if (mlx->interf->id_select_obj < mlx->scene->nb_obj)
				mlx->scene->objs[mlx->interf->id_select_obj]->pos.z++;
			else
				mlx->scene->spot[mlx->interf->id_select_obj -
					mlx->scene->nb_obj]->pos.z++;
		}
		else
		{
			mlx->scene->cam->pos.z += 5;
			init_camera(mlx);
		}
		render(mlx);
	}
}

static void	antialiasing_key(t_mlx *mlx, int key)
{
	if (key == PAGE_UP)
		mlx->aa *= 2;
	if (key == PAGE_DOWN)
		mlx->aa /= 2;
	if (mlx->aa < 1)
		mlx->aa = 1;
	if (mlx->aa > 8)
		mlx->aa = 8;
}

int			key_func(int key, void *p)
{
	t_mlx *mlx;

	mlx = (t_mlx*)p;
	if (key == ESC)
		exit(0);
	if (key == UP)
		key_up(mlx);
	if (key == DOWN)
		key_down(mlx);
	if (key == RIGHT)
		key_right(mlx);
	if (key == LEFT)
		key_left(mlx);
	if (key == MORE)
		key_minus(mlx);
	if (key == LESS)
		key_plus(mlx);
	antialiasing_key(mlx, key);
	key_rot(mlx, key);
	if (key == L)
		mlx->scene->light = (mlx->scene->light) ? 0 : 1;
	display_interface(mlx);
	return (1);
}
