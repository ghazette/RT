/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fetch.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/06 12:08:00 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/03 12:12:52 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rt.h"

static int		fetch_help_next(t_obj *obj, char ***split)
{
	if (!ft_strcmp((*split)[0], "height"))
		obj->height = llabs(ft_atoi((*split)[1]));
	if (!ft_strcmp((*split)[0], "width"))
		obj->width = llabs(ft_atoi((*split)[1]));
	if (!ft_strcmp((*split)[0], "depth"))
		obj->depth = llabs(ft_atoi((*split)[1]));
	if (!ft_strcmp((*split)[0], "src"))
		fetch_obj((*split)[1], &obj);
	if (!ft_strcmp((*split)[0], "reflection"))
		obj->material.reflectivity = fabs(ft_atof((*split)[1]));
	if (!ft_strcmp((*split)[0], "refraction"))
		obj->material.refraction = fabs(ft_atof((*split)[1]));
	ft_free2d(split);
	return (1);
}

static int		fetch_object_array_help(t_obj *obj, char **split)
{
	if (!ft_strcmp(split[0], "name"))
		if (split[1] && !obj->name)
		{
			if (ft_strlen(split[1]) > 10)
				split[1][10] = '\0';
			if (!(obj->name = ft_strdup(split[1])))
				return (0);
		}
	if (!ft_strcmp(split[0], "radius"))
		obj->radius = llabs(ft_atoi(split[1]));
	if (!ft_strcmp(split[0], "specular"))
	{
		if (ft_heightlen(split) == 4)
		{
			if (!(init_vec(&obj->material.specular, split)))
				return (0);
			vec3_normalizeby(&obj->material.specular, 255);
		}
	}
	if (!ft_strcmp(split[0], "ambient"))
		if ((obj->material.ambient = fabs(ft_atof(split[1])) < 0))
			return (0);
	return (fetch_help_next(obj, &split));
}

static int		fetch_object_array(t_obj *obj, char **split)
{
	if (!ft_strcmp(split[0], "position"))
		if (!(init_vec(&obj->pos, split)))
			return (0);
	if (!ft_strcmp(split[0], "rotation") && obj->type != 0)
	{
		if (!(init_vec(&obj->rot, split)))
			return (0);
	}
	if (!ft_strcmp(split[0], "color"))
	{
		if (!(init_vec(&obj->color, split)))
			return (0);
		vec3_normalizeby(&obj->color, 255);
	}
	if (!ft_strcmp(split[0], "type") && split[1])
		if (!(obj->type = type_define(split[1], obj)))
			return (0);
	if (!ft_strcmp(split[0], "texture"))
		if (split[1] && !(obj->texture.data = import_bmp(split[1],
						&(obj->texture.width), &(obj->texture.height))))
			return (0);
	if (!ft_strcmp(split[0], "form") && split[1])
		if (!(obj->form = form_define(split[1], obj)))
			return (0);
	return (fetch_object_array_help(obj, split));
}

static int		fetch_obj_next(t_mlx *mlx, char **line)
{
	mlx->scene->objs[mlx->scene->nb_obj]->id = mlx->scene->nb_obj;
	if (!check_object(&mlx->aaoff, mlx->scene->objs[mlx->scene->nb_obj]))
		return (0);
	if (mlx->scene->objs[mlx->scene->nb_obj]->type >= SPHERE)
		rotate(mlx->scene->objs[mlx->scene->nb_obj]);
	mlx->scene->nb_obj++;
	ft_strdel(line);
	return (1);
}

int				fetch_object(t_mlx *mlx, int fd)
{
	int		i;
	char	*line;
	char	**split;

	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		mlx->line_cnt++;
		if (ft_strchr(line, '{'))
		{
			i = 1;
			if (!(mlx->scene->objs[mlx->scene->nb_obj] = new_object()))
				return (0);
		}
		if (!i)
			return (0);
		if (ft_strchr(line, '}'))
			return (fetch_obj_next(mlx, &line));
		if (!(ft_parser_secure(line, &split)))
			return (0);
		if (!fetch_object_array(mlx->scene->objs[mlx->scene->nb_obj], split))
			return (0);
		ft_strdel(&line);
	}
	return (0);
}
