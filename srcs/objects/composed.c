/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   composed.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/07 13:09:07 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/11 14:17:44 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rtv1.h"



static int		is_inbound(t_interinfo *interinfo, t_obj *obj, t_vec3 *view, t_vec3 vdir)
{
	t_vec3	vc;
	t_vec3	vp;
	int		i;
	int		j;
	double	t;
	double a;
	double b;
	int	c;
	double dist, tmpdist;
	int ab = 0;
	t_interinfo interinfo_tmp;

	i = 0;
	dist = 99999999;
	tmpdist = 0;
	while (i < obj->npoly)
	{
		t = (vec3_dotproduct(&obj->poly[i]->n, obj->poly[i]->s[0]) -
		vec3_dotproduct(&obj->poly[i]->n, view)) / vec3_dotproduct(&obj->poly[i]->n, &vdir);
		vec3_add(view, vec3_scale(&vdir, t, MULT, &interinfo->intersect),
			&interinfo->intersect);
		vector3d(&interinfo->normal, obj->poly[i]->n.x, obj->poly[i]->n.y, obj->poly[i]->n.z);
		t_vec3 test;
		vec3_sub(&interinfo->intersect, &obj->poly[i]->n, &test);
		a = vec3_length(&interinfo->intersect, view);
		b = vec3_length(&test, view);
		j = 0;
		c = 1;
		ab = 0;
		while (j < obj->poly[i]->ns)
		{
			vec3_sub(&interinfo->intersect, obj->poly[i]->s[j], &vp);
			vec3_crossproduct(obj->poly[i]->e[j], &vp, &vc);
			if (a > b)
			{
				ab = a > b;
				if (vec3_dotproduct(&obj->poly[i]->n, &vc) < 0)
					c = 0;
			}
			else if (vec3_dotproduct(&obj->poly[i]->n, &vc) > 0)
				c = 0;
			j++;
		}
		if (c == 1)
		{
			tmpdist = vec3_length(&interinfo->intersect, view);
			if (tmpdist < dist)
			{
				dist = tmpdist;
				inter_cpy(&interinfo_tmp, interinfo);
				if (ab)
					vec3_reverse(&interinfo_tmp.normal);
			}
		}
		if (a > b && c == 1)
		 	vec3_reverse(&interinfo->normal);
		i++;
	}
	if (dist != 99999999)
	{
		inter_cpy(interinfo, &interinfo_tmp);
		return (1);
	}
	return (0);
}

int				render_composed(t_interinfo *interinfo, t_vec3 *view, t_obj *obj, t_vec3 vdir)
{
	if (!(is_inbound(interinfo, obj, view, vdir)))
		return (0);
	return (1);
}
