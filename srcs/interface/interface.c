/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   interface.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/12 13:56:48 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/12 11:45:56 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rt.h"

int				display_obj_attr(t_mlx *mlx, t_obj *obj, char *str, int y)
{
	double	color;
	char	*vec;

	color = (obj->id == mlx->interf->id_select_obj) ? 0xFF0000 : 0x00FF00;
	if (y > BTNHEIGHT)
		mlx_string_put(mlx->mlx, mlx->win, WIN_W + 2, y, color, "OBJECT");
	ft_strcat(ft_strcpy(str, "name: "), obj->name);
	if (y > BTNHEIGHT)
		mlx_string_put(mlx->mlx, mlx->win, WIN_W + 2, y += 20, 0xFFFFFF, str);
	if (!(vec = parse_vec(obj->pos)))
		return (y);
	ft_strcat(ft_strcpy(str, "position: "), vec);
	if (y > BTNHEIGHT)
		mlx_string_put(mlx->mlx, mlx->win, WIN_W + 2, y += 20, 0xFFFFFF, str);
	ft_strdel(&vec);
	ft_strcat(ft_strcpy(str, "type: "), get_type(obj->type));
	if (y > BTNHEIGHT)
		mlx_string_put(mlx->mlx, mlx->win, WIN_W + 2, y += 20, 0xFFFFFF, str);
	y += 40;
	return (y);
}

static void		display_object(t_mlx *mlx)
{
	char	str[200];
	int		i;
	int		y;

	ft_bzero(str, 200);
	i = -1;
	y = 120 + BTNHEIGHT + mlx->interf->offset;
	while (++i < mlx->scene->nb_obj)
		y = display_obj_attr(mlx, mlx->scene->objs[i], str, y);
	i = -1;
	while (++i < mlx->scene->nb_spot)
		y = display_spot(mlx, mlx->scene->spot[i], str, y);
}

static void		display_scene_next(t_mlx *mlx, char *str)
{
	if (mlx->interf->offset + BTNHEIGHT + 5 > BTNHEIGHT)
		mlx_string_put(mlx->mlx, mlx->win, WIN_W + 2, BTNHEIGHT + 5 +
			mlx->interf->offset, 0xFFFFFF, "SCENE");
	ft_strcat(ft_strcpy(str, "name: "), mlx->scene->name);
	if (mlx->interf->offset + BTNHEIGHT + 20 > BTNHEIGHT)
		mlx_string_put(mlx->mlx, mlx->win, WIN_W + 2, BTNHEIGHT + 20 +
			mlx->interf->offset, 0xFFFFFF, str);
}

static void		display_scene(t_mlx *mlx)
{
	char str[200];
	char *nb;

	ft_bzero(str, 200);
	display_scene_next(mlx, str);
	if (!(nb = ft_itoa(WIN_W)))
		return ;
	ft_strcat(ft_strcpy(str, "resolution: "), nb);
	ft_strdel(&nb);
	if (!(nb = ft_itoa(WIN_H)))
		return ;
	ft_strcat(ft_strcat(str, "x"), nb);
	ft_strdel(&nb);
	if (mlx->interf->offset + BTNHEIGHT + 35 > BTNHEIGHT)
		mlx_string_put(mlx->mlx, mlx->win, WIN_W + 2, BTNHEIGHT + 35 +
			mlx->interf->offset, 0xFFFFFF, str);
	ft_bzero(str, 200);
	if (!(nb = ft_itoa(mlx->aa)))
		return ;
	ft_strcat(ft_strcat(str, "anti-aliasing: "), nb);
	if (mlx->interf->offset + BTNHEIGHT + 50 > BTNHEIGHT)
		mlx_string_put(mlx->mlx, mlx->win, WIN_W + 2, BTNHEIGHT + 50 +
			mlx->interf->offset, 0xFFFFFF, str);
	ft_strdel(&nb);
}

int				display_interface(t_mlx *mlx)
{
	int y;

	y = 0;
	clear_interface(mlx);
	while (y < WIN_H)
		mlx_pixel_put(mlx->mlx, mlx->win, WIN_W, y++, 0xFFFFFFF);
	export_button(mlx, 0xCD7F32);
	display_scene(mlx);
	display_camera(mlx);
	display_object(mlx);
	display_focus(mlx);
	return (1);
}
