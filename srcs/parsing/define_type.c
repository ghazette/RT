/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   define_type.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlossy <rlossy@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/01 13:24:40 by rlossy       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/01 13:24:40 by rlossy      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rt.h"

int				check_object(int *aaoff, t_obj *obj)
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
			calc_cube(obj);
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

int				form_define(char *form, t_obj *obj)
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

static int		type_define_next(char *type, t_obj *obj)
{
	if (!ft_strcmp("CYLINDER", type))
	{
		obj->render_func = render_cylinder;
		vector3d(&obj->dir, 0, 1, 0);
		return (CYLINDER);
	}
	else if (!ft_strcmp("CONE", type))
	{
		obj->render_func = render_cone;
		vector3d(&obj->dir, 0, 1, 0);
		return (CONE);
	}
	else if (!ft_strcmp("PLANE", type))
	{
		obj->render_func = render_plane;
		vector3d(&obj->dir, 0, 0, -1);
		return (PLANE);
	}
	else if (!ft_strcmp("COMPOSED", type))
	{
		obj->render_func = render_composed;
		vector3d(&obj->dir, 0, 0, 1);
		return (COMPOSED);
	}
	return (0);
}

int				type_define(char *type, t_obj *obj)
{
	if (!ft_strcmp("SPHERE", type))
	{
		obj->render_func = render_sphere;
		return (SPHERE);
	}
	if (!ft_strcmp("CYLINDER", type))
		return (type_define_next(type, obj));
	if (!ft_strcmp("CONE", type))
		return (type_define_next(type, obj));
	if (!ft_strcmp("PLANE", type))
		return (type_define_next(type, obj));
	if (!ft_strcmp("COMPOSED", type))
		return (type_define_next(type, obj));
	return (0);
}
