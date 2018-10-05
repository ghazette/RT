/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fetch2.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/10 11:37:24 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 11:55:31 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rt.h"

static int	fetch_spot_array(t_spot *spot, char **split)
{
	if (!ft_strcmp(split[0], "name"))
		if (split[1] && !spot->name)
		{
			if (ft_strlen(split[1]) > 10)
				split[1][10] = '\0';
			if (!(spot->name = ft_strdup(split[1])))
				return (0);
		}
	if (!ft_strcmp(split[0], "color"))
	{
		if (!(init_vec(&(spot->color), split)))
			return (0);
		vec3_normalizeby(&(spot->color), 255);
	}
	if (!ft_strcmp(split[0], "specular"))
	{
		if (!(init_vec(&(spot->material.specular), split)))
			return (0);
		vec3_normalizeby(&(spot->material.specular), 255);
	}
	if (!ft_strcmp(split[0], "ambient"))
		if ((spot->material.ambient = ft_atoi(split[1]) / 100.0) < 0)
			return (0);
	return (fetch_spot_array_help(spot, split));
}

static int	fetch_spot_next(t_mlx *mlx, t_spot **spot, t_fetch *f)
{
	if (!f->i[0] && mlx->line_cnt++ > -1 && ft_strchr(f->line, '{'))
	{
		f->i[0] = 1;
		if (!(*spot = new_spot()))
			return (0);
	}
	return (1);
}

int			fetch_spot(t_mlx *mlx, t_spot **spot, int fd)
{
	t_fetch	f;

	ft_bzero(&f, sizeof(t_fetch));
	while (get_next_line(fd, &f.line) > 0)
	{
		if (!(fetch_spot_next(mlx, spot, &f)))
			return (0);
		if (ft_strchr(f.line, '}') && f.i[0])
		{
			f.i[1] = 1;
			if (!(*spot)->name && !((*spot)->name = ft_strdup("NONE")))
				return (0);
			ft_strdel(&f.line);
			return (mlx->scene->light = 1);
		}
		if (!(ft_parser_secure(f.line, &f.split)))
			return (0);
		if (!(fetch_spot_array(*spot, f.split)))
			return (0);
		ft_free2d(&f.split);
		ft_strdel(&f.line);
	}
	if (f.i[0] && f.i[1])
		return (1);
	return (0);
}

static int	fetch_camera_array(t_cam *cam, char **split)
{
	if (!ft_strcmp(split[0], "position"))
	{
		if (!(init_vec(&cam->pos, split)))
			return (0);
		vector3d(&cam->npos, cam->pos.x, cam->pos.y, cam->pos.z);
		vec3_normalize(&cam->npos);
	}
	if (!ft_strcmp(split[0], "focal"))
	{
		cam->viewplane_dist = ft_atoi(split[1]);
		if (cam->viewplane_dist < 1)
			cam->viewplane_dist = 1;
	}
	if (!ft_strcmp(split[0], "resolution"))
	{
		cam->res[0] = ft_atoi(split[1]);
		cam->res[1] = ft_atoi(split[2]);
	}
	if (!ft_strcmp(split[0], "lookat"))
		if (!(init_vec(&cam->lookat, split)))
			return (0);
	if (!ft_strcmp(split[0], "rotation"))
		if (!(init_vec(&cam->rot, split)))
			return (0);
	return (1);
}

int			fetch_camera(t_mlx *mlx, int fd)
{
	char *line;
	char **split;

	while (get_next_line(fd, &line) > 0)
	{
		mlx->line_cnt++;
		if (ft_strchr(line, '{') && ft_strchr(line, '}'))
			return (0);
		if (ft_strchr(line, '}'))
		{
			ft_strdel(&line);
			return (1);
		}
		if (!(ft_parser_secure(line, &split)))
			return (0);
		fetch_camera_array(mlx->scene->cam, split);
		ft_free2d(&split);
		ft_strdel(&line);
	}
	return (0);
}
