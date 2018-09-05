/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   key_rot.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/08 06:13:06 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/11 16:29:27 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

static void	reset_rot(t_cam *cam, t_obj *obj)
{
	if (cam)
		vector3d(&cam->rot, 0, 0, 0);
	if (obj)
		vector3d(&obj->rot, 0, 0, 0);
}

static void	rot_object(t_obj *obj, int key)
{
	if (key == 86)
		obj->rot.y = -2;
	if (key == 88)
		obj->rot.y = 2;
	if (key == 91)
		obj->rot.x = -2;
	if (key == 84)
		obj->rot.x = 2;
	if (key == 89)
		obj->rot.z = 2;
	if (key == 92)
		obj->rot.z = -2;
}

static void	rot_camera(t_cam *cam, int key)
{
	if (key == 86)
		cam->rot.y -= 5;
	if (key == 88)
		cam->rot.y += 5;
	if (key == 91)
		cam->rot.x -= 5;
	if (key == 84)
		cam->rot.x += 5;
	if (key == 89)
		cam->rot.z += 5;
	if (key == 92)
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
