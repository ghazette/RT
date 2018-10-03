/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   obj_cpy.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlossy <rlossy@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/28 15:59:14 by rlossy       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 16:14:52 by rlossy      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rt.h"

static int		cpy_texture(t_sce *scene, t_sce *src, int i)
{
	size_t	size;

	if (src->objs[i]->texture.data)
	{
		size = (4 * src->objs[i]->texture.width) * src->objs[i]->texture.height;
		if (!(scene->objs[i]->texture.data = malloc(sizeof(char) * size)))
			return (0);
		ft_memcpy(scene->objs[i]->texture.data, src->objs[i]->texture.data,
					size);
		scene->objs[i]->texture.width = src->objs[i]->texture.width;
		scene->objs[i]->texture.height = src->objs[i]->texture.height;
	}
	else
		scene->objs[i]->texture.data = NULL;
	return (1);
}

static void		poly_cpy(t_poly **poly, t_poly *src)
{
	int i;

	i = 0;
	(*poly) = malloc(sizeof(t_poly));
	(*poly)->s = malloc(sizeof(t_vec3*) * src->ns);
	(*poly)->e = malloc(sizeof(t_vec3*) * src->ns);
	(*poly)->ns = src->ns;
	vec3_cpy(&(*poly)->n, &src->n);
	while (i < (*poly)->ns)
	{
		(*poly)->s[i] = malloc(sizeof(t_vec3));
		(*poly)->e[i] = malloc(sizeof(t_vec3));
		vec3_cpy((*poly)->s[i], src->s[i]);
		vec3_cpy((*poly)->e[i], src->e[i]);
		i++;
	}
}

static void		obj_cpy_next(t_sce *scene, t_sce *src, int i)
{
	scene->objs[i]->radius = src->objs[i]->radius;
	vector3d(&(scene->objs[i]->pos), src->objs[i]->pos.x, src->objs[i]->pos.y,
		src->objs[i]->pos.z);
	vector3d(&(scene->objs[i]->dir), src->objs[i]->dir.x, src->objs[i]->dir.y,
		src->objs[i]->dir.z);
	vector3d(&(scene->objs[i]->rot), src->objs[i]->rot.x, src->objs[i]->rot.y,
		src->objs[i]->rot.z);
	vector3d(&(scene->objs[i]->color), src->objs[i]->color.x,
		src->objs[i]->color.y, src->objs[i]->color.z);
	scene->objs[i]->material.ambient = src->objs[i]->material.ambient;
	scene->objs[i]->material.reflectivity = src->objs[i]->material.reflectivity;
	scene->objs[i]->material.refraction = src->objs[i]->material.refraction;
	vector3d(&(scene->objs[i]->material.color), src->objs[i]->material.color.x,
		src->objs[i]->material.color.y, src->objs[i]->material.color.z);
	vector3d(&(scene->objs[i]->material.specular),
		src->objs[i]->material.specular.x, src->objs[i]->material.specular.y,
		src->objs[i]->material.specular.z);
	scene->objs[i]->render_func = src->objs[i]->render_func;
}

static void		obj_polycpy(const t_sce *scene, const t_sce *src, int i)
{
	int j;

	j = -1;
	scene->objs[i]->form = src->objs[i]->form;
	scene->objs[i]->poly = (t_poly**)malloc(sizeof(t_poly*)
											* src->objs[i]->npoly);
	scene->objs[i]->npoly = src->objs[i]->npoly;
	while (++j < scene->objs[i]->npoly)
		poly_cpy(&scene->objs[i]->poly[j], src->objs[i]->poly[j]);
}

int				obj_cpy(t_sce *scene, t_sce *src)
{
	int	i;

	i = -1;
	if (!(scene->objs = (t_obj**)malloc(sizeof(t_obj*) * scene->nb_obj)))
		return (0);
	while (++i < scene->nb_obj)
	{
		scene->objs[i] = (t_obj*)malloc(sizeof(t_obj));
		scene->objs[i]->id = src->objs[i]->id;
		scene->objs[i]->havenormal = src->objs[i]->havenormal;
		scene->objs[i]->type = src->objs[i]->type;
		if (scene->objs[i]->type == COMPOSED)
			obj_polycpy(scene, src, i);
		if (!(scene->objs[i]->name = ft_strdup(src->objs[i]->name)))
			return (0);
		obj_cpy_next(scene, src, i);
		if (!(cpy_texture(scene, src, i)))
			return (0);
	}
	return (1);
}
