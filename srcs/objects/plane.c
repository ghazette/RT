/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   plane.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/10 17:15:22 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/11 09:34:52 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rt.h"

int	render_plane(t_interinfo *interinfo, t_vec3 *view, t_obj *obj, t_vec3 vdir)
{
	double	t;
	t_vec3	length;

	t = (vec3_dotproduct(&obj->dir, &obj->pos) -
		vec3_dotproduct(&obj->dir, view)) / vec3_dotproduct(&obj->dir, &vdir);
	if (t < 0)
		return (0);
	vec3_add(view, vec3_scale(&vdir, t, MULT, &interinfo->intersect),
		&interinfo->intersect);
	vector3d(&interinfo->normal, obj->dir.x, obj->dir.y, obj->dir.z);
	vec3_sub(&interinfo->intersect, &obj->dir, &length);
	if (vec3_length(&interinfo->intersect, view) > vec3_length(&length, view))
		vec3_reverse(&interinfo->normal);
	return (1);
}
