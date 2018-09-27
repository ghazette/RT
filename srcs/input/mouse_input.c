/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mouse_input.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/12 16:12:35 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/25 11:46:43 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

int			mouse_func(int button, int x, int y, t_mlx *mlx)
{
	if (button == LEFT_CLICK)
		left_click(mlx, x, y);
	if (button == SCROLL_UP)
		scroll_up(mlx, x, y);
	if (button == SCROLL_DOWN)
		scroll_down(mlx, x, y);
	display_interface(mlx);
	return (1);
}

int			motion_func(int x, int y, t_mlx *mlx)
{
	if (x > WIN_W && x < WIN_W + INTER_WIDTH && y > 0 && y < BTNHEIGHT)
		export_button(mlx, 0xA46528);
	else
		export_button(mlx, 0xCD7F32);
	return (1);
}
