/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   plane.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/10 17:15:22 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 17:56:30 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

static int shape_intersect(t_obj *obj, t_interinfo *interinfo)
{
	t_vec3 C;
	t_vec3 vp;
	double res;

	vec3_sub(&interinfo->intersect, &(obj)->shape.v0, &vp);
	vec3_crossproduct(&obj->shape.e0, &vp, &C);
	if (vec3_dotproduct(&obj->dir, &C) < 0)
		return (0);
	vec3_sub(&interinfo->intersect, &(obj)->shape.v1, &vp);
	vec3_crossproduct(&obj->shape.e1, &vp, &C);
	if (vec3_dotproduct(&obj->dir, &C) < 0)
		return (0);
	vec3_sub(&interinfo->intersect, &(obj)->shape.v2, &vp);
	vec3_crossproduct(&obj->shape.e2, &vp, &C);
	if (vec3_dotproduct(&obj->dir, &C) < 0.0001)
		return (0);
	return (1);
}

int	render_plane(t_interinfo *interinfo, t_vec3 *view, t_obj *obj, t_vec3 vdir)
{
	double t;

	t = (vec3_dotproduct(&obj->dir, &obj->pos) -
		vec3_dotproduct(&obj->dir, view)) / vec3_dotproduct(&obj->dir, &vdir);
	if (t < 0)
		return (0);
	vec3_add(view, vec3_scale(&vdir, t, MULT, &interinfo->intersect),
		&interinfo->intersect);
	if (obj->shape.len >= 3)
		if (!shape_intersect(obj, interinfo))
			return (0);
	vector3d(&interinfo->normal, obj->dir.x, obj->dir.y, obj->dir.z);
	t_vec3 test;
	vec3_sub(&interinfo->intersect, &obj->dir, &test);
	double a = vec3_length(&interinfo->intersect, view);
	double b = vec3_length(&test, view);
	if (a > b)
	{
		vec3_reverse(&interinfo->normal);
	}
	return (1);
}
