/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   interface1.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/12 15:54:17 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/07 17:52:34 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

void			clear_interface(t_mlx *mlx)
{
	int x;
	int y;

	x = WIN_W;
	while (x < WIN_W + INTER_WIDTH)
	{
		y = 0;
		while (y < WIN_H)
		{
			mlx_pixel_put(mlx->mlx, mlx->win, x, y, 0x0000);
			y++;
		}
		x++;
	}
}

void			display_focus(t_mlx *mlx)
{
	int x;
	int y;

	x = WIN_W - 105;
	while (x < WIN_W)
	{
		y = 0;
		while (y < 30)
			mlx_pixel_put(mlx->mlx, mlx->win, x, y++, 0x0000);
		x++;
	}
	if (mlx->interf->focus == 0)
		mlx_string_put(mlx->mlx, mlx->win, WIN_W - 87, 5, 0xFFFFFF, "window");
	else
		mlx_string_put(mlx->mlx, mlx->win, WIN_W - 100, 5, 0xFFFFFF,
			"interface");
}

int				inter_select_up(t_mlx *mlx)
{
	if (mlx->interf->id_select_obj == -1)
		return (1);
	else
		mlx->interf->id_select_obj--;
	return (0);
}

int				inter_select_down(t_mlx *mlx)
{
	if (mlx->interf->id_select_obj < mlx->scene->nb_obj +
		mlx->scene->nb_spot - 1)
		mlx->interf->id_select_obj++;
	return (0);
}

int				display_spot(t_mlx *mlx, t_spot *obj, char *str, int y)
{
	double	color;
	char	*vec;

	color = (obj->id == mlx->interf->id_select_obj) ? 0xFF0000 : 0x00FF00;
	if (y > BTNHEIGHT)
		mlx_string_put(mlx->mlx, mlx->win, WIN_W + 2, y, color, "SPOT");
	ft_strcat(ft_strcpy(str, "name: "), obj->name);
	if (y > BTNHEIGHT)
		mlx_string_put(mlx->mlx, mlx->win, WIN_W + 2, y += 20, 0xFFFFFF, str);
	if (!(vec = parse_vec(obj->pos)))
		return (y);
	ft_strcat(ft_strcpy(str, "position: "), vec);
	ft_strdel(&vec);
	if (y > BTNHEIGHT)
		mlx_string_put(mlx->mlx, mlx->win, WIN_W + 2, y += 20, 0xFFFFFF, str);
	y += 40;
	return (y);
}
