/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fetch_data.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlossy <rlossy@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/01 13:43:48 by rlossy       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/01 13:43:48 by rlossy      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rt.h"

static int	fetch_data_next(t_mlx *mlx, char **line)
{
	if ((*line)[0] == 'A' && (*line)[1] == 'A')
	{
		mlx->aa = ft_atoi((*line) + 2);
		if (mlx->aa < 1 || mlx->aa > 4)
			mlx->aa = 1;
		ft_strdel(line);
		return (1);
	}
	if ((*line)[0] == 'A' && (*line)[1] == 'M' && (*line)[2] == 'B')
	{
		mlx->ambient = (double)ft_atoi((*line) + 3) / 100.0;
		if (mlx->ambient < 0)
			mlx->ambient = 0.1;
		ft_strdel(line);
		return (1);
	}
	ft_strdel(line);
	return (0);
}

int			fetch_data(t_mlx *mlx, int fd)
{
	char *line;

	line = NULL;
	if (get_next_line(fd, &line) <= 0)
		return (1);
	mlx->line_cnt++;
	if (!ft_strcmp(line, "CAMERA"))
	{
		ft_strdel(&line);
		return (fetch_camera(mlx, fd));
	}
	if (!ft_strcmp(line, "OBJECT"))
	{
		ft_strdel(&line);
		return (fetch_object(mlx, fd));
	}
	if (!ft_strcmp(line, "SPOT"))
	{
		ft_strdel(&line);
		return (fetch_spot(mlx, &mlx->scene->spot[mlx->scene->nb_spot++], fd));
	}
	return (fetch_data_next(mlx, &line));
}
