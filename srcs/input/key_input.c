/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   key_input.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/20 15:31:37 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/06 14:51:21 by ghazette    ###    #+. /#+    ###.fr     */
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

int			key_func(int key, void *p)
{
	t_mlx *mlx;

	mlx = (t_mlx*)p;
	if (key == 53)
		exit(0);
	if (key == 126)
		key_up(mlx);
	if (key == 125)
		key_down(mlx);
	if (key == 124)
		key_right(mlx);
	if (key == 123)
		key_left(mlx);
	if (key == 69)
		key_minus(mlx);
	if (key == 78)
		key_plus(mlx);
	key_rot(mlx, key);
	if (key == 37)
		mlx->scene->light = (mlx->scene->light) ? 0 : 1;
	display_interface(mlx);
	return (1);
}
