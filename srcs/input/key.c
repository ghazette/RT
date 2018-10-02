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

#include "../../includes/rt.h"

void	mv_cmp(t_obj **obj, char c, int sign)
{
	int		i;
	int		j;
	double	*ptr_s;

	i = 0;
	while (i < (*obj)->npoly)
	{
		j = 0;
		while (j < (*obj)->poly[i]->ns)
		{
			ptr_s = (c == 'x') ? &(*obj)->poly[i]->s[j]->x : ptr_s;
			ptr_s = (c == 'y') ? &(*obj)->poly[i]->s[j]->y : ptr_s;
			ptr_s = (c == 'z') ? &(*obj)->poly[i]->s[j]->z : ptr_s;
			if (sign == ADD)
				(*ptr_s)++;
			else if (sign == SUB)
				(*ptr_s)--;
			j++;
			ptr_s = 0;
		}
		calc_edge((*obj)->poly[i], 0, 0);
		i++;
	}
}

void	key_up(t_mlx *mlx, t_interface *interf)
{
	if (interf->focus)
		inter_select_up(mlx);
	else
	{
		if (interf->id_select_obj != -1)
		{
			if (interf->id_select_obj < mlx->scene->nb_obj)
			{
				if (mlx->scene->objs[interf->id_select_obj]->type == COMPOSED)
					mv_cmp(&mlx->scene->objs[interf->id_select_obj], 'y', ADD);
				mlx->scene->objs[interf->id_select_obj]->pos.y++;
			}
			else
				mlx->scene->spot[interf->id_select_obj -
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

void	key_down(t_mlx *mlx, t_interface *interf)
{
	if (interf->focus)
		inter_select_down(mlx);
	else
	{
		if (interf->id_select_obj != -1)
		{
			if (interf->id_select_obj < mlx->scene->nb_obj)
			{
				if (mlx->scene->objs[interf->id_select_obj]->type == COMPOSED)
					mv_cmp(&mlx->scene->objs[interf->id_select_obj], 'y', SUB);
				mlx->scene->objs[interf->id_select_obj]->pos.y--;
				vec3_reverse(&(mlx->scene->objs[interf->id_select_obj]->dir));
			}
			else
				mlx->scene->spot[interf->id_select_obj -
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

void	key_right(t_mlx *mlx, t_interface *interf)
{
	if (!interf->focus)
	{
		if (interf->id_select_obj != -1)
		{
			if (interf->id_select_obj < mlx->scene->nb_obj)
			{
				if (mlx->scene->objs[interf->id_select_obj]->type ==
					COMPOSED)
					mv_cmp(&mlx->scene->objs[interf->id_select_obj], 'x', ADD);
				mlx->scene->objs[interf->id_select_obj]->pos.x++;
			}
			else
				mlx->scene->spot[interf->id_select_obj -
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

void	key_left(t_mlx *mlx, t_interface *interf)
{
	if (!interf->focus)
	{
		if (interf->id_select_obj != -1)
		{
			if (interf->id_select_obj < mlx->scene->nb_obj)
			{
				if (mlx->scene->objs[interf->id_select_obj]->type == COMPOSED)
					mv_cmp(&mlx->scene->objs[interf->id_select_obj], 'x', SUB);
				mlx->scene->objs[interf->id_select_obj]->pos.x--;
			}
			else
				mlx->scene->spot[interf->id_select_obj -
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
