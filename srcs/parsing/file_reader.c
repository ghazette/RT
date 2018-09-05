/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   file_reader.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/21 13:59:22 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 11:20:32 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

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
	ft_strdel(&line);
	return (0);
}

static int	set_obj_spot(t_mlx *mlx, char **split, char *fn)
{
	int nb[2];

	if (!(get_nb_obj(fn, nb)))
		return (0);
	if (!(mlx->scene->objs = (t_obj**)malloc(sizeof(t_obj*) * nb[0])))
		return (0);
	if (!(mlx->scene->spot = (t_spot**)malloc(sizeof(t_spot*) * nb[1])))
		return (0);
	return (1);
}

static int	init_scene_help(t_mlx *mlx, char *name, char *fn, char **split)
{
	if (!name)
		return (0);
	if (ft_strlen(name) > 10)
		name[10] = '\0';
	if (!(mlx->scene->name = ft_strdup(name)))
		return (0);
	mlx->scene->nb_obj = 0;
	mlx->scene->nb_spot = 0;
	mlx->scene->light = 1;
	mlx->interf->id_select_obj = -1;
	mlx->interf->offset = 0;
	mlx->interf->focus = 0;
	if (!(set_obj_spot(mlx, split, fn)))
		return (0);
	return (1);
}

int			init_scene(t_mlx *mlx, char *fn, int fd)
{
	char	*line;
	char	**split;
	int		nb[2];

	if (!check_file(fn))
		return (0);
	get_next_line(fd, &line);
	if (!(split = ft_strsplit(line, ' ')))
		return (0);
	ft_strdel(&line);
	if (!ft_strcmp(split[0], "#SCENE"))
	{
		if (!(mlx->scene = malloc(sizeof(t_sce))))
			return (0);
		if (!(mlx->scene->interinfo = malloc(sizeof(t_interinfo))))
			return (0);
		if (!new_camera(mlx))
			return (0);
		if (!(init_scene_help(mlx, split[1], fn, split)))
			return (0);
		ft_free2d(&split);
		return (1);
	}
	return (0);
}

int			open_file(t_mlx *mlx, char *fn)
{
	int		fd;
	char	*line;
	int		err;

	line = NULL;
	if (!check_dir(fn) && (line = NULL) == NULL)
		return (0);
	if ((fd = open(fn, O_RDONLY)) < 0 || !(init_scene(mlx, fn, fd)))
		return (0);
	while ((err = fetch_data(mlx, fd)))
	{
		if (get_next_line(fd, &line) <= 0 && mlx->line_cnt++ > -1)
			break ;
		if (ft_strcmp(line, ""))
			return (0);
		ft_strdel(&line);
	}
	close(fd);
	ft_strdel(&line);
	if (!err)
		return (0);
	err = -1;
	while (++err < mlx->scene->nb_spot)
		mlx->scene->spot[err]->id = mlx->scene->nb_obj + err;
	return (1);
}
