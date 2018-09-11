/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fetch.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/06 12:08:00 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/11 13:23:41 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

static int		type_define(char *type, t_obj *obj)
{
	if (!ft_strcmp("SPHERE", type))
	{
		obj->render_func = render_sphere;
		return (SPHERE);
	}
	if (!ft_strcmp("CYLINDER", type))
	{
		obj->render_func = render_cylinder;
		vector3d(&obj->dir, 0, 1, 0);
		return (CYLINDER);
	}
	if (!ft_strcmp("CONE", type))
	{
		obj->render_func = render_cone;
		vector3d(&obj->dir, 0, 1, 0);
		return (CONE);
	}
	if (!ft_strcmp("PLANE", type))
	{
		obj->render_func = render_plane;
		obj->npoly = 4;
		vector3d(&obj->dir, 0, 0, -1);
		return (PLANE);
	}
	if (!ft_strcmp("COMPOSED", type))
	{
		obj->render_func = render_composed;
		vector3d(&obj->dir, 0, 0, 1);
		obj->poly = (t_poly**)malloc(sizeof(t_poly*) * obj->npoly);
		return (COMPOSED);
	}
	return (0);
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
		obj->radius = ft_atoi(split[1]);
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
		if ((obj->material.ambient = (double)ft_atoi(split[1]) / 100.0) < 0)
			return (0);
	if (!ft_strcmp(split[0], "height"))
		obj->height = ft_atoi(split[1]);
	if (!ft_strcmp(split[0], "width"))
		obj->width = ft_atoi(split[1]);
	ft_free2d(&split);
	return (1);
}

int				calc_edge(t_poly *poly, int nvertex)
{
	int i;

	i = 0;
	while (i < nvertex  - 1)
	{
		vec3_sub(poly->s[i], poly->s[i + 1], poly->e[i]);
		i++;
	}
	vec3_sub(poly->s[i], poly->s[0], poly->e[i]);
	vec3_crossproduct(poly->e[0], poly->e[1], poly->n);
	vec3_normalize(poly->n);
	return (1);
}

int				fetch_poly(char *str, t_obj **obj)
{
	int		i;
	char	**split;
	char	**vsplit;
	int		nvertex;

	i = -1;
	
	split = ft_strsplit(str, ';');
	nvertex = ft_heightlen(split);
	(*obj)->npoly--;
	(*obj)->poly[(*obj)->npoly] = malloc(sizeof(t_poly*));
	(*obj)->poly[(*obj)->npoly]->s = (t_vec3**)malloc(sizeof(t_vec3*) * nvertex);
	(*obj)->poly[(*obj)->npoly]->e = (t_vec3**)malloc(sizeof(t_vec3*) * nvertex);
	while (++i < nvertex)
	{
		vsplit = ft_strsplit(split[i], '_');
		(*obj)->poly[(*obj)->npoly]->s[i] = malloc(sizeof(t_vec3));
		(*obj)->poly[(*obj)->npoly]->e[i] = malloc(sizeof(t_vec3));
		(*obj)->poly[(*obj)->npoly]->s[i]->x = ft_atoi(vsplit[0]);
		(*obj)->poly[(*obj)->npoly]->s[i]->y = ft_atoi(vsplit[1]);
		(*obj)->poly[(*obj)->npoly]->s[i]->z = ft_atoi(vsplit[2]);
	}
	calc_edge((*obj)->poly[(*obj)->npoly], nvertex);
	return (1);
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
		if (split[1] && !(obj->texture.data = import_bmp(split[1], &(obj->texture.width), &(obj->texture.height))))
			return (0);
	if (!ft_strcmp(split[0], "obj_src") && split[1])
		if (!(fetch_obj(split[1], &obj)))
			return (0);
	if (!ft_strcmp(split[0], "poly") && split[1] && obj->type == COMPOSED)
		if (!(fetch_poly(split[1], &obj)))
			return (0);
	if (!ft_strcmp(split[0], "nb_poly") && split[1]) {
		if (!(obj->npoly = ft_atoi(split[1])))
			return (0);
	}
	return (fetch_object_array_help(obj, split));
}

static int		check_object(t_obj *obj)
{
	if (!obj->name)
		if (!(obj->name = ft_strdup("NONE")))
			return (0);
	if (!obj->type)
		return (0);
	return (1);
}

int				fetch_object(t_mlx *mlx, int fd)
{
	char *line;

	while (get_next_line(fd, &line))
	{
		mlx->line_cnt++;
		if (!ft_strcmp(line, "{"))
			if (!(mlx->scene->objs[mlx->scene->nb_obj] = new_object()))
				return (0);
		if (!ft_strcmp(line, "}"))
		{
			mlx->scene->objs[mlx->scene->nb_obj]->id = mlx->scene->nb_obj;
			if (!check_object(mlx->scene->objs[mlx->scene->nb_obj]))
				return (0);
			if (mlx->scene->objs[mlx->scene->nb_obj]->type >= SPHERE)
				rotate(mlx->scene->objs[mlx->scene->nb_obj]);
			mlx->scene->nb_obj++;
			ft_strdel(&line);
			return (1);
		}
		if (!ft_strcmp(line, ""))
			return (0);
		if (!fetch_object_array(mlx->scene->objs[mlx->scene->nb_obj],
			ft_strsplit(line, ' ')))
			return (0);
		ft_strdel(&line);
	}
	return (0);
}