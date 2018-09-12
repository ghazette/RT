/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   key_rot.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/08 06:13:06 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/12 10:52:34 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

static void	reset_rot(t_cam *cam, t_obj *obj)
{
	if (cam)
		vector3d(&cam->rot, 0, 0, 0);
	if (obj && obj->type != SPHERE)
		vector3d(&obj->rot, 0, 0, 0);
}

static void	rot_object(t_obj *obj, int key)
{
	if (key == FOUR)
		obj->rot.y += 8;
	if (key == SIX)
		obj->rot.y -= 8;
	if (key == EIGHT)
		obj->rot.x += 8;
	if (key == TWO)
		obj->rot.x -= 8;
	if (key == SEVEN)
		obj->rot.z += 8;
	if (key == NINE)
		obj->rot.z -= 8;
}

static void	rot_camera(t_cam *cam, int key)
{
	if (key == FOUR)
		cam->rot.y += 5;
	if (key == SIX)
		cam->rot.y -= 5;
	if (key == EIGHT)
		cam->rot.x += 5;
	if (key == TWO)
		cam->rot.x -= 5;
	if (key == SEVEN)
		cam->rot.z += 5;
	if (key == NINE)
		cam->rot.z -= 5;
}

void		key_rot(t_mlx *mlx, int key)
{
	if (!mlx->interf->focus)
	{
		if (mlx->interf->id_select_obj != -1)
		{
			if (mlx->interf->id_select_obj < mlx->scene->nb_obj)
			{
				rot_object(mlx->scene->objs[mlx->interf->id_select_obj]
					, key);
				rotate(mlx->scene->objs[mlx->interf->id_select_obj]);
				reset_rot(NULL, mlx->scene->objs[mlx->interf->id_select_obj]);
			}
		}
		else
		{
			rot_camera(mlx->scene->cam, key);
			init_camera(mlx);
		}
		render(mlx);
	}
}
