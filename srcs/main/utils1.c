/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils1.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/23 23:35:52 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/19 10:58:07 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

void		inter_cpy(t_interinfo *dest, t_interinfo *src)
{
	vector3d(&dest->intersect, src->intersect.x,
		src->intersect.y, src->intersect.z);
	vector3d(&dest->normal, src->normal.x, src->normal.y, src->normal.z);
}

void		export_button(t_mlx *mlx, int color)
{
	int x;
	int y;

	x = WIN_W + 1;
	while (x < WIN_W + INTER_WIDTH)
	{
		y = 0;
		while (y < BTNHEIGHT)
			mlx_pixel_put(mlx->mlx, mlx->win, x, y++, color);
		x++;
	}
	mlx_string_put(mlx->mlx, mlx->win, WIN_W + 70, BTNHEIGHT / 2 - 10, 0xFFFFFF,
		"EXPORT BMP");
}

t_obj		*new_object(void)
{
	t_obj *obj;

	if (!(obj = malloc(sizeof(t_obj))))
		return (NULL);
	obj->id = 0;
	obj->name = NULL;
	obj->type = 0;
	obj->radius = 0;
	obj->texture.data = NULL;
	obj->width = 0;
	obj->height = 0;
	vector3d(&obj->pos, 0, 0, 0);
	vector3d(&obj->rot, 0, 0, 0);
	vector3d(&obj->dir, 0, 0, 0);
	vector3d(&obj->color, 0, 0, 0);
	vector3d(&obj->material.specular, 200.0 / 255.0, 200.0 / 255.0,
		150.0 / 255.0);
	obj->material.ambient = 0.03;
	obj->material.reflectivity = 0;
	obj->material.refraction = 1.0;
	return (obj);
}

t_spot		*new_spot(void)
{
	t_spot *spot;

	if (!(spot = malloc(sizeof(t_spot))))
		return (NULL);
	spot->name = NULL;
	vector3d(&spot->pos, 0, 0, 0);
	vector3d(&spot->color, 1, 1, 1);
	vector3d(&spot->material.specular, 0, 0, 0);
	spot->material.ambient = 0.05;
	return (spot);
}

int			new_camera(t_mlx *mlx)
{
	t_cam	*cam;

	if (!(cam = malloc(sizeof(t_cam))))
		return (0);
	vector3d(&cam->pos, 0, 0, -100);
	vector3d(&cam->rot, 0, 0, 0);
	vector3d(&cam->lookat, 0, 0, 1);
	cam->viewplane_dist = 1;
	mlx->scene->cam = cam;
	return (1);
}
