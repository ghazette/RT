/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sphere.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/06 12:13:10 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/06 17:53:24 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

int		render_sphere(t_interinfo *interinfo, t_vec3 *view,
	t_obj *obj, t_vec3 vdir)
{
	t_calc		sph;

	vec3_sub(view, &obj->pos, &sph.ray);
	sph.b = vec3_dotproduct(&sph.ray, &vdir);
	sph.c = vec3_sqrlength(&sph.ray) - (obj->radius * obj->radius);
	sph.delta = ((sph.b * sph.b) - sph.c);
	if (sph.delta < 0)
		return (0);
	sph.t = (-sph.b);
	if (sph.delta != 0)
	{
		sph.delta = sqrt(sph.delta);
		sph.t1 = (-sph.b + sph.delta);
		sph.t2 = (-sph.b - sph.delta);
		sph.t = (sph.t1 < sph.t2) ? sph.t : sph.t2;
	}
	if (sph.t < 0)
		return (0);
	vec3_add(view, vec3_scale(&vdir, sph.t, MULT, &interinfo->intersect),
		&interinfo->intersect);
	vec3_scale(vec3_sub(&interinfo->intersect, &obj->pos,
		&interinfo->normal), obj->radius, DIV, &interinfo->normal);
	vec3_normalize(&interinfo->normal);
	return (1);
}
