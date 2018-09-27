/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   key.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/23 23:21:54 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/25 11:36:05 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

void	key_up(t_mlx *mlx)
{
	if (mlx->interf->focus)
		inter_select_up(mlx);
	else
	{
		if (mlx->interf->id_select_obj != -1)
		{
			if (mlx->interf->id_select_obj < mlx->scene->nb_obj)
				mlx->scene->objs[mlx->interf->id_select_obj]->pos.y++;
			else
				mlx->scene->spot[mlx->interf->id_select_obj -
					mlx->scene->nb_obj]->pos.y++;
		}
		else
		{
			mlx->scene->cam->pos.y += 5;
			mlx->scene->cam->lookat.y += 5;
			init_camera(mlx);
			render(mlx);
		}
		
	}
}

void	key_down(t_mlx *mlx)
{
	if (mlx->interf->focus)
		inter_select_down(mlx);
	else
	{
		if (mlx->interf->id_select_obj != -1)
		{
			if (mlx->interf->id_select_obj < mlx->scene->nb_obj)
			{
				mlx->scene->objs[mlx->interf->id_select_obj]->pos.y--;
				vec3_reverse(
						&(mlx->scene->objs[mlx->interf->id_select_obj]->dir));
			}
			else
				mlx->scene->spot[mlx->interf->id_select_obj -
					mlx->scene->nb_obj]->pos.y--;
		}
		else
		{
			mlx->scene->cam->pos.y -= 5;
			mlx->scene->cam->lookat.y -= 5;
			init_camera(mlx);
			render(mlx);
		}
	}
}

void	key_right(t_mlx *mlx)
{
	if (!mlx->interf->focus)
	{
		if (mlx->interf->id_select_obj != -1)
		{
			if (mlx->interf->id_select_obj < mlx->scene->nb_obj)
				mlx->scene->objs[mlx->interf->id_select_obj]->pos.x++;
			else
				mlx->scene->spot[mlx->interf->id_select_obj -
					mlx->scene->nb_obj]->pos.x++;
		}
		else
		{
			mlx->scene->cam->pos.x += 5;
			mlx->scene->cam->lookat.x += 5;
			init_camera(mlx);
			render(mlx);
		}
	}
}

void	key_left(t_mlx *mlx)
{
	if (!mlx->interf->focus)
	{
		if (mlx->interf->id_select_obj != -1)
		{
			if (mlx->interf->id_select_obj < mlx->scene->nb_obj)
				mlx->scene->objs[mlx->interf->id_select_obj]->pos.x--;
			else
				mlx->scene->spot[mlx->interf->id_select_obj -
					mlx->scene->nb_obj]->pos.x--;
		}
		else
		{
			mlx->scene->cam->pos.x -= 5;
			mlx->scene->cam->lookat.x -= 5;
			init_camera(mlx);
			render(mlx);
		}
	}
}
