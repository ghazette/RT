/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cylinder.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/17 16:18:02 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/06 13:57:46 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rt.h"

static void		cylinder_calc_normal(t_interinfo *interinfo, t_obj *obj)
{
	double	hyp;
	double	adj;

	hyp = vec3_length(&obj->pos, &interinfo->intersect);
	adj = sqrt((hyp * hyp) - (obj->radius * obj->radius));
	vector3d(&interinfo->normal,
		obj->pos.x + (adj * obj->dir.x),
		obj->pos.y + (adj * obj->dir.y),
		obj->pos.z + (adj * obj->dir.z));
	if (isnan(adj))
	{
		vec3_sub(&interinfo->intersect, &obj->pos, &interinfo->normal);
		vec3_normalize(&interinfo->normal);
		return ;
	}
	if (vec3_length(&interinfo->intersect, &obj->pos) <
	vec3_length(&interinfo->normal, &interinfo->intersect))
	{
		vector3d(&interinfo->normal,
			obj->pos.x + (-adj * obj->dir.x),
			obj->pos.y + (-adj * obj->dir.y),
			obj->pos.z + (-adj * obj->dir.z));
	}
	vec3_sub(&interinfo->intersect, &interinfo->normal, &interinfo->normal);
	vec3_normalize(&interinfo->normal);
}

int				render_cylinder(t_interinfo *interinfo, t_vec3 *view,
	t_obj *obj, t_vec3 vdir)
{
	t_calc cyl;
	double dsqrt;

	vec3_sub(view, &obj->pos, &cyl.ray);
	cyl.val[0] = vec3_dotproduct(&vdir, &obj->dir);
	cyl.val[1] = vec3_dotproduct(&cyl.ray, &obj->dir);
	cyl.a = vec3_dotproduct(&vdir, &vdir) - (cyl.val[0] * cyl.val[0]);
	cyl.b = vec3_dotproduct(&cyl.ray, &vdir) - (cyl.val[1] * cyl.val[0]);
	cyl.c = vec3_dotproduct(&cyl.ray, &cyl.ray) -
		(cyl.val[1] * cyl.val[1]) - (obj->radius * obj->radius);
	if ((cyl.delta = (cyl.b * cyl.b) - cyl.a * cyl.c) <= 0)
		return (0);
	dsqrt = sqrt(cyl.delta);
	cyl.t1 = (-cyl.b + dsqrt) / cyl.a;
	cyl.t2 = (-cyl.b - dsqrt) / cyl.a;
	if (cyl.t1 > cyl.t2)
		ft_doubleswap(&cyl.t1, &cyl.t2);
	if (cyl.t1 < 0)
		return (0);
	vec3_add(view, vec3_scale(&vdir, cyl.t1, MULT,
		&interinfo->intersect), &interinfo->intersect);
	cylinder_calc_normal(interinfo, obj);
	return (1);
}
