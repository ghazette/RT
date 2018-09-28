/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   key.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/23 23:21:54 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 17:45:33 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

void	move_composed(t_obj **obj, char c, int sign)
{
	int i;
	int j;
	double *ptr_s;
	double *ptr_e;

	i = 0;
	while (i < (*obj)->npoly)
	{
		j = 0;
		while (j < (*obj)->poly[i]->ns)
		{
			if (c == 'x')
			{
				ptr_s = &(*obj)->poly[i]->s[j]->x;
				ptr_e = &(*obj)->poly[i]->e[j]->x;
			}
			if (c == 'y')
			{
				ptr_s = &(*obj)->poly[i]->s[j]->y;
				ptr_e = &(*obj)->poly[i]->e[j]->y;
			}
			if (c == 'z')
			{
				ptr_s = &(*obj)->poly[i]->s[j]->z;
				ptr_e = &(*obj)->poly[i]->e[j]->z;
			}
			if (sign == ADD)
				(*ptr_s)++;
			else if (sign == SUB)
				(*ptr_s)--;
			j++;
			ptr_s = 0;
		}
		calc_edge((*obj)->poly[i], 0);
		i++;
	}
}

void	key_up(t_mlx *mlx)
{
	if (mlx->interf->focus)
		inter_select_up(mlx);
	else
	{
		if (mlx->interf->id_select_obj != -1)
		{
			if (mlx->interf->id_select_obj < mlx->scene->nb_obj)
			{
				if (mlx->scene->objs[mlx->interf->id_select_obj]->type == COMPOSED)
					move_composed(&mlx->scene->objs[mlx->interf->id_select_obj], 'y', ADD);
				mlx->scene->objs[mlx->interf->id_select_obj]->pos.y++;
			}
			else
				mlx->scene->spot[mlx->interf->id_select_obj -
					mlx->scene->nb_obj]->pos.y++;
		}
		else
		{
			mlx->scene->cam->pos.y += 5;
			mlx->scene->cam->lookat.y += 5;
			init_camera(mlx);
		}
		render(mlx);
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
				if (mlx->scene->objs[mlx->interf->id_select_obj]->type == COMPOSED)
					move_composed(&mlx->scene->objs[mlx->interf->id_select_obj], 'y', SUB);
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
		}
		render(mlx);
	}
}

void	key_right(t_mlx *mlx)
{
	if (!mlx->interf->focus)
	{
		if (mlx->interf->id_select_obj != -1)
		{
			if (mlx->interf->id_select_obj < mlx->scene->nb_obj)
			{
				if (mlx->scene->objs[mlx->interf->id_select_obj]->type ==
					COMPOSED)
					move_composed(&mlx->scene->objs[mlx->interf->id_select_obj], 'x', ADD);
				mlx->scene->objs[mlx->interf->id_select_obj]->pos.x++;
			}
			else
				mlx->scene->spot[mlx->interf->id_select_obj -
					mlx->scene->nb_obj]->pos.x++;
		}
		else
		{
			mlx->scene->cam->pos.x += 5;
			mlx->scene->cam->lookat.x += 5;
			init_camera(mlx);
		}
		render(mlx);
	}
}

void	key_left(t_mlx *mlx)
{
	if (!mlx->interf->focus)
	{
		if (mlx->interf->id_select_obj != -1)
		{
			if (mlx->interf->id_select_obj < mlx->scene->nb_obj)
			{
				if (mlx->scene->objs[mlx->interf->id_select_obj]->type == COMPOSED)
					move_composed(&mlx->scene->objs[mlx->interf->id_select_obj], 'x', SUB);
				mlx->scene->objs[mlx->interf->id_select_obj]->pos.x--;
			}
			else
				mlx->scene->spot[mlx->interf->id_select_obj -
					mlx->scene->nb_obj]->pos.x--;
		}
		else
		{
			mlx->scene->cam->pos.x -= 5;
			mlx->scene->cam->lookat.x -= 5;
			init_camera(mlx);
		}
		render(mlx);
	}
}
