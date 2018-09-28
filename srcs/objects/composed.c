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

static t_interinfo	inoutside_next(t_interinfo *interinfo, t_vec3 *view,
									double *ab, int c)
{
	double		tmpdist;
	t_interinfo	interinfo_tmp;

	tmpdist = 0;
	if (c == 1)
	{
		tmpdist = vec3_length(&interinfo->intersect, view);
		if (tmpdist < interinfo->dist)
		{
			interinfo->dist = tmpdist;
			if (ab[0] > ab[1])
				vec3_reverse(&interinfo->normal);
			inter_cpy(&interinfo_tmp, interinfo);
		}
	}
	return (interinfo_tmp);
}

static t_interinfo	inoutside(t_interinfo *interinfo, t_poly *poly,
							t_vec3 *view, t_vec3 test)
{
	int		c;
	int		j;
	double	ab[2];
	t_vec3	vp;
	t_vec3	vc;

	ab[0] = vec3_length(&interinfo->intersect, view);
	ab[1] = vec3_length(&test, view);
	c = 1;
	j = -1;
	while (++j < poly->ns)
	{
		vec3_sub(&interinfo->intersect, poly->s[j], &vp);
		vec3_crossproduct(poly->e[j], &vp, &vc);
		if (ab[0] > ab[1])
		{
			if (vec3_dotproduct(&interinfo->normal, &vc) < 0)
				c = 0;
		}
		else if (vec3_dotproduct(&interinfo->normal, &vc) > 0)
			c = 0;
	}
	return(inoutside_next(interinfo, view, ab, c));
}

static int			is_inbound(t_interinfo *interinfo, t_obj *obj, t_vec3 *view, t_vec3 vdir)
{
	int			c;
	int			i;
	int			j;
	double		t;
	double		a;
	double		b;
	double		dist;
	double		tmpdist;
	t_vec3		vp;
	t_vec3		vc;
	t_vec3		test;
	t_interinfo	interinfo_tmp;

	i = -1;
	interinfo->dist = 99999999;
	tmpdist = 0;
	while (++i < obj->npoly)
	{
		t = (vec3_dotproduct(&obj->poly[i]->n, obj->poly[i]->s[0]) -
		vec3_dotproduct(&obj->poly[i]->n, view)) / vec3_dotproduct(&obj->poly[i]->n, &vdir);
		if (t < 0)
			continue;
		vec3_add(view, vec3_scale(&vdir, t, MULT, &interinfo->intersect),
			&interinfo->intersect);
		vector3d(&interinfo->normal, obj->poly[i]->n.x, obj->poly[i]->n.y, obj->poly[i]->n.z);
		vec3_sub(&interinfo->intersect, &obj->poly[i]->n, &test);
		// interinfo_tmp = inoutside(interinfo, obj->poly[i], view, test);
		a = vec3_length(&interinfo->intersect, view);
		b = vec3_length(&test, view);
		j = -1;
		c = 1;
		while (++j < obj->poly[i]->ns)
		{
			vec3_sub(&interinfo->intersect, obj->poly[i]->s[j], &vp);
			vec3_crossproduct(obj->poly[i]->e[j], &vp, &vc);
			if (a > b)
			{
				if (vec3_dotproduct(&interinfo->normal, &vc) < 0)
					c = 0;
			}
			else if (vec3_dotproduct(&interinfo->normal, &vc) > 0)
				c = 0;
		}
		if (c == 1)
		{
			tmpdist = vec3_length(&interinfo->intersect, view);
			if (tmpdist < interinfo->dist)
			{
				interinfo->dist = tmpdist;
				if (a > b)
					vec3_reverse(&interinfo->normal);
				inter_cpy(&interinfo_tmp, interinfo);
			}
		}
	}
	if (interinfo->dist != 99999999)
		return (inter_cpy(interinfo, &interinfo_tmp));
	return (0);
}

int				render_composed(t_interinfo *interinfo, t_vec3 *view,
								t_obj *obj, t_vec3 vdir)
{
	if (!(is_inbound(interinfo, obj, view, vdir)))
		return (0);
	return (1);
}
