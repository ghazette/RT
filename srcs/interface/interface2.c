/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   interface2.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlossy <rlossy@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/28 13:28:38 by rlossy       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 13:28:38 by rlossy      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rt.h"

void	display_camera(t_mlx *mlx)
{
	char	str[200];
	char	*vec;
	double	color;

	ft_bzero(str, 200);
	color = (mlx->interf->id_select_obj == -1) ? 0xFF0000 : 0x0000FF;
	if (mlx->interf->offset + 70 + BTNHEIGHT > BTNHEIGHT)
		mlx_string_put(mlx->mlx, mlx->win, WIN_W + 2, 70 + BTNHEIGHT +
				mlx->interf->offset, color, "CAMERA");
	if (!(vec = parse_vec(mlx->scene->cam->pos)))
		return ;
	ft_strcat(ft_strcpy(str, "position: "), vec);
	ft_strdel(&vec);
	if (mlx->interf->offset + BTNHEIGHT + 85 > BTNHEIGHT)
		mlx_string_put(mlx->mlx, mlx->win, WIN_W + 2, 85 + BTNHEIGHT +
				mlx->interf->offset, 0xFFFFFF, str);
}
