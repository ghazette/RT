/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fetch.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/06 12:08:00 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/27 16:48:45 by ghazette    ###    #+. /#+    ###.fr     */
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
		vector3d(&obj->dir, 0, 0, -1);
		return (PLANE);
	}
	if (!ft_strcmp("COMPOSED", type))
	{
		obj->render_func = render_composed;
		vector3d(&obj->dir, 0, 0, 1);
		return (COMPOSED);
	}
	return (0);
}

static int		form_define(char *form, t_obj *obj)
{
	if (!ft_strcmp("CUBE", form))
	{
		obj->npoly = 6;
		return (CUBE);
	}
	if (!ft_strcmp("OBJ_FROMFILE", form))
		return (OBJ_FROMFILE);
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
		if ((obj->material.ambient = fabs((double)ft_atoi(split[1]) / 100.0) < 0))
			return (0);
	if (!ft_strcmp(split[0], "height"))
		obj->height = llabs(ft_atoi(split[1]));
	if (!ft_strcmp(split[0], "width"))
		obj->width = ft_atoi(split[1]);
	if (!ft_strcmp(split[0], "depth"))
		obj->depth = ft_atoi(split[1]);
	if (!ft_strcmp(split[0], "src"))
		return (fetch_obj(split[1], &obj));
		obj->width = llabs(ft_atoi(split[1]));
	if (!ft_strcmp(split[0], "reflection"))
		obj->material.reflectivity = fabs(ft_atof(split[1]));
	if (!ft_strcmp(split[0], "refraction"))
		obj->material.refraction = fabs(ft_atof(split[1]));
	ft_free2d(&split);
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
		if (split[1] && !(obj->texture.data = import_bmp(split[1],
						&(obj->texture.width), &(obj->texture.height))))
			return (0);
	if (!ft_strcmp(split[0], "form") && split[1])
		if (!(obj->form = form_define(split[1], obj)))
			return (0);
	return (fetch_object_array_help(obj, split));
}

int calc_edge(t_poly *poly, int calcnormal)
{
	int i;
	t_vec3 v0;
	t_vec3 v1;

	i = 1;
	poly->e = malloc(sizeof(t_vec3*) * poly->ns);
	while (i < poly->ns)
	{
		poly->e[i - 1] = malloc(sizeof(t_vec3));
		vec3_sub(poly->s[i - 1], poly->s[i], poly->e[i - 1]);
		i++;
	}
	poly->e[i - 1] = malloc(sizeof(t_vec3));
	poly->e[i - 1] = vec3_sub(poly->s[i - 1], poly->s[0], poly->e[i - 1]);
	if (calcnormal)
	{
		vec3_sub(poly->e[1], poly->e[0], &v0);
		vec3_sub(poly->e[2], poly->e[0], &v1);
		vec3_crossproduct(&v0, &v1, &poly->n);
		vec3_normalize(&poly->n);
	}
	return (1);
}

static t_poly *new_poly(t_poly *poly, int ns, t_vec3 *p, int *index)
{
	int i;

	i = 0;
	poly = malloc(sizeof(t_poly));
	poly->ns = ns;
	poly->s = malloc(sizeof(t_vec3*) * ns);
	while (i < ns)
	{
		poly->s[i] = malloc(sizeof(t_vec3));
		poly->s[i] = vector3d(poly->s[i], p[index[i]].x, p[index[i]].y, p[index[i]].z);
		i++;
	}
	calc_edge(poly, 1);
	return (poly);
}

int calc_cube(t_obj *obj)
{
	int i;
	int j;
	double x;
	double y;
	double z;

	double h;
	double w;
	double d;
	t_vec3 p[8];
	int index[4];


	x = obj->pos.x;
	y = obj->pos.y;
	z = obj->pos.z;
	h = (double)obj->height / 2;
	w = (double)obj->width / 2;
	d = (double)obj->depth / 2;
	vector3d(&p[0], x - w, y + h, z - d);
	vector3d(&p[1], x + w, y + h, z - d);
	vector3d(&p[2], x + w, y - h, z - d);
	vector3d(&p[3], x - w, y - h, z - d);
	vector3d(&p[4], x - w, y + h, z + d);
	vector3d(&p[5], x + w, y + h, z + d);
	vector3d(&p[6], x + w, y - h, z + d);
	vector3d(&p[7], x - w, y - h, z + d);
	obj->poly = malloc(sizeof(t_poly*) * obj->npoly);
	index[0] = 0;
	index[1] = 1;
	index[2] = 2;
	index[3] = 3;
	obj->poly[0] = new_poly(obj->poly[0], 4, p, index);
	index[0] = 1;
	index[1] = 5;
	index[2] = 6;
	index[3] = 2;
	obj->poly[1] = new_poly(obj->poly[1], 4, p, index);
	index[0] = 5;
	index[1] = 4;
	index[2] = 7;
	index[3] = 6;
	obj->poly[2] = new_poly(obj->poly[2], 4, p, index);
	index[0] = 0;
	index[1] = 3;
	index[2] = 7;
	index[3] = 4;
	obj->poly[3] = new_poly(obj->poly[3], 4, p, index);
	index[0] = 0;
	index[1] = 4;
	index[2] = 5;
	index[3] = 1;
	obj->poly[4] = new_poly(obj->poly[4], 4, p, index);
	index[0] = 3;
	index[1] = 2;
	index[2] = 6;
	index[3] = 7;
	obj->poly[5] = new_poly(obj->poly[5], 4, p, index);
	return (1);
}

static int calc_poly(t_obj *obj)
{
	if (obj->form == CUBE)
		calc_cube(obj);
	return (0);
}

static int		check_object(int *aaoff, t_obj *obj)
{
	if (!obj->name)
		if (!(obj->name = ft_strdup("NONE")))
			return (0);
	if (!obj->type)
		return (0);
	if (obj->type == COMPOSED)
	{
		obj->width = (!obj->width) ? 1 : obj->width;
		obj->height = (!obj->height) ? 1 : obj->height;
		obj->depth = (!obj->depth) ? 1 : obj->depth;
		if (obj->form == CUBE)
			calc_poly(obj);
		else if (obj->form == OBJ_FROMFILE)
			return (1);
		else
			return (0);
	}
	if (obj->type == CONE)
		obj->material.refraction = 0;
	if (obj->material.refraction > 0.0)
		obj->material.reflectivity = 1.0;
	if (obj->material.refraction > 0.0 || obj->material.reflectivity > 0.0)
		*aaoff = 1;
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
			if (!check_object(&mlx->aaoff, mlx->scene->objs[mlx->scene->nb_obj]))
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
			ft_splitwhitespace(line)))
			return (0);
		ft_strdel(&line);
	}
	return (0);
}
