/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   composed.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/07 13:09:07 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/19 12:55:31 by rlossy      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

static int		is_inbound(t_interinfo *interinfo, t_obj *obj, t_vec3 *view,
							t_vec3 vdir)
{
	int		c;
	int		i;
	int		j;
	double	t;
	double	a;
	double	b;
	t_vec3	vc;
	t_vec3	vp;
	t_vec3	test;

	i = 0;
	while (obj->poly[i] != 0)
	{
		t = (vec3_dotproduct(obj->poly[i]->n, obj->poly[i]->s[0]) -
		vec3_dotproduct(obj->poly[i]->n, view)) /
				vec3_dotproduct(obj->poly[i]->n, &vdir);
		if (t < 0)
			return (0);
		vec3_add(view, vec3_scale(&vdir, t, MULT, &interinfo->intersect),
			&interinfo->intersect);
		vector3d(&interinfo->normal, obj->poly[i]->n->x, obj->poly[i]->n->y,
				obj->poly[i]->n->z);
		vec3_sub(&interinfo->intersect, obj->poly[i]->n, &test);
		a = vec3_length(&interinfo->intersect, view);
		b = vec3_length(&test, view);
		j = 0;
		c = 0;
		while (obj->poly[i]->e[j] != 0)
		{
			vec3_sub(&interinfo->intersect, obj->poly[i]->s[j], &vp);
			vec3_crossproduct(obj->poly[i]->e[j], &vp, &vc);
			// if (a > b && vec3_dotproduct(obj->poly[i]->n, &vc) < 0)
			// 	c = 1;
			// else if (vec3_dotproduct(obj->poly[i]->n, &vc) > 0)
			// 	c = 1;
			if (vec3_dotproduct(obj->poly[i]->n, &vc) < 0)
				c = 1;
			j++;
		}
		if (a > b && c == 1)
			vec3_reverse(&interinfo->normal);
		if (c == 1)
			return (1);
		i++;
	}
	return (0);
}

int				render_composed(t_interinfo *interinfo, t_vec3 *view,
								t_obj *obj, t_vec3 vdir)
{
	if (!(is_inbound(interinfo, obj, view, vdir)))
		return (0);
	return (1);
}
