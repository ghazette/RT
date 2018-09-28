/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   key_input.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/20 15:31:37 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/27 16:45:14 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

static void	key_minus(t_mlx *mlx)
{
	t_interface *interf;

	interf = mlx->interf;
	if (!interf->focus)
	{
		if (interf->id_select_obj != -1)
		{
			if (interf->id_select_obj < mlx->scene->nb_obj)
			{
				if (mlx->scene->objs[interf->id_select_obj]->type == COMPOSED)
					mv_cmp(&mlx->scene->objs[interf->id_select_obj], 'z', SUB);
				mlx->scene->objs[interf->id_select_obj]->pos.z--;
			}
			else
				mlx->scene->spot[interf->id_select_obj -
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
	t_interface *interf;

	interf = mlx->interf;
	if (!interf->focus)
	{
		if (interf->id_select_obj != -1)
		{
			if (interf->id_select_obj < mlx->scene->nb_obj)
			{
				if (mlx->scene->objs[interf->id_select_obj]->type == COMPOSED)
					mv_cmp(&mlx->scene->objs[interf->id_select_obj], 'z', ADD);
				mlx->scene->objs[interf->id_select_obj]->pos.z++;
			}
			else
				mlx->scene->spot[interf->id_select_obj -
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

static void	ft_effect_key(t_mlx *mlx, int key)
{
	if (!mlx->aaoff)
	{
		if (key == PAGE_UP && mlx->aa < 4)
			mlx->aa *= 2;
		if (key == PAGE_DOWN && mlx->aa > 1)
			mlx->aa /= 2;
	}
	if (key == F)
		mlx->effect = (mlx->effect < 6) ? mlx->effect += 1 : 0;
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
	ft_effect_key(mlx, key);
	key_rot(mlx, key);
	if (key == L)
		mlx->scene->light = (mlx->scene->light) ? 0 : 1;
	display_interface(mlx);
	return (1);
}
