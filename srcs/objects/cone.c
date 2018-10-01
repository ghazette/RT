/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cone.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/16 16:22:01 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/08 14:02:12 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rt.h"

static void		cone_calc_normal(t_interinfo *interinfo, t_obj *obj,
	double angle)
{
	double	hyp;

	hyp = vec3_length(&interinfo->intersect, &obj->pos) / cos(angle / 2);
	vector3d(&interinfo->normal,
		obj->pos.x + (hyp * obj->dir.x),
		obj->pos.y + (hyp * obj->dir.y),
		obj->pos.z + (hyp * obj->dir.z));
	if (vec3_length(&interinfo->intersect, &obj->pos) <
		vec3_length(&interinfo->normal, &interinfo->intersect))
		vector3d(&interinfo->normal,
			obj->pos.x + (-hyp * obj->dir.x),
			obj->pos.y + (-hyp * obj->dir.y),
			obj->pos.z + (-hyp * obj->dir.z));
	vec3_sub(&interinfo->intersect, &interinfo->normal, &interinfo->normal);
	vec3_normalize(&interinfo->normal);
}

int				render_cone(t_interinfo *interinfo, t_vec3 *view, t_obj *obj,
t_vec3 vdir)
{
	t_calc	cone;

	vec3_sub(view, &obj->pos, &cone.ray);
	cone.angle = cos(obj->radius * TORAD) * cos(obj->radius * TORAD);
	cone.val[0] = vec3_dotproduct(&vdir, &obj->dir);
	cone.val[1] = vec3_dotproduct(&cone.ray, &obj->dir);
	cone.a = (cone.val[0] * cone.val[0]) - cone.angle;
	cone.b = 2 * (cone.val[0] * cone.val[1] - vec3_dotproduct(&vdir, &cone.ray)
	* cone.angle);
	cone.c = (cone.val[1] * cone.val[1]) - vec3_dotproduct(&cone.ray, &cone.ray)
	* cone.angle;
	if ((cone.delta = (cone.b * cone.b) - 4 * cone.a * cone.c) < 0)
		return (0);
	cone.t1 = (cone.delta == 0) ? -cone.b / (2 * cone.a) : 0;
	if (cone.delta > 0)
	{
		if ((cone.t1 = (-cone.b - sqrt(cone.delta)) / (2 * cone.a)) < 0)
			return (0);
		cone.t2 = (-cone.b + sqrt(cone.delta)) / (2 * cone.a);
	}
	vec3_add(view, vec3_scale(&vdir, (cone.t1 > cone.t2) ? cone.t2 : cone.t1,
	MULT, &interinfo->intersect),
	&interinfo->intersect);
	cone_calc_normal(interinfo, obj, cone.angle);
	return (1);
}
