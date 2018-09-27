/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   click.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/23 23:10:17 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/25 11:40:05 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

int			export_bmp(t_mlx *mlx)
{
	char *fn;
	char *dir;
	char *final;

	if (!(fn = rand_string(7)))
		return (0);
	if (!(dir = ft_strjoin("./image/", fn)))
		return (0);
	if (!(final = ft_strjoin(dir, ".bmp")))
		return (0);
	export_as_bmp(final, mlx->pixel_img, WIN_W, WIN_H);
	ft_strdel(&fn);
	ft_strdel(&dir);
	ft_strdel(&final);
	return (1);
}

void		left_click(t_mlx *mlx, int x, int y)
{
	if (x > WIN_W && x < WIN_W + INTER_WIDTH && y > 0 && y < BTNHEIGHT)
		export_bmp(mlx);
	else if (x > WIN_W && y > 60)
		mlx->interf->focus = 1;
	else
		mlx->interf->focus = 0;
}

void		scroll_up(t_mlx *mlx, int x, int y)
{
	if (x > WIN_W && y > BTNHEIGHT)
		mlx->interf->offset -= 25;
}

void		scroll_down(t_mlx *mlx, int x, int y)
{
	if (x > WIN_W && y > BTNHEIGHT)
		mlx->interf->offset += 25;
}
