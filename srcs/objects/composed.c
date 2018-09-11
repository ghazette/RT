/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   composed.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mkulhand <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/07 13:09:07 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/07 13:09:08 by mkulhand    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

static int		is_inbound(t_interinfo *interinfo, t_obj *obj, t_vec3 *view, t_vec3 vdir)
{
	t_vec3	C;
	t_vec3	vp;
	int		i;
	int		j;
	double	t;
	double a;
	double b;

	i = 0;
	while (obj->poly[i] != NULL)
	{
		t = (vec3_dotproduct(&obj->poly[i]->n, &obj->pos) -
		vec3_dotproduct(&obj->poly[i]->n, view)) / vec3_dotproduct(&obj->poly[i]->n, &vdir);
		if (t < 0)
			return (0);
		vec3_add(view, vec3_scale(&vdir, t, MULT, &interinfo->intersect),
			&interinfo->intersect);
		vector3d(&interinfo->normal, obj->poly[i]->n.x, obj->poly[i]->n.y, obj->poly[i]->n.z);
		t_vec3 test;
		vec3_sub(&interinfo->intersect, &obj->poly[i]->n, &test);
		a = vec3_length(&interinfo->intersect, view);
		b = vec3_length(&test, view);
		j = 0;
		while (obj->poly[i]->e[j] != NULL)
		{
			vec3_sub(&interinfo->intersect, obj->poly[i]->s[j], &vp);
			vec3_crossproduct(obj->poly[i]->e[j], &vp, &C);
			if (a > b)
			{
				if (vec3_dotproduct(&obj->poly[i]->n, &C) < 0)
					break;
			}
			else if (vec3_dotproduct(&obj->poly[i]->n, &C) > 0)
				break;
			j++;
		}
		if (a > b)
			vec3_reverse(&interinfo->normal);
		i++;
	}
	return (1);
}

int				render_composed(t_interinfo *interinfo, t_vec3 *view, t_obj *obj, t_vec3 vdir)
{
	if (!(is_inbound(interinfo, obj, view, vdir)))
		return (0);
	return (1);
}
