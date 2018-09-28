/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   composed.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/07 13:09:07 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 14:34:54 by rlossy      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

static void			inoutside(t_interinfo *interinfo, t_poly *poly,
								t_vec3 *view, t_inbound *inbd)
{
	inbd->j = -1;
	inbd->c = 1;
	while (++inbd->j < poly->ns)
	{
		vec3_sub(&interinfo->intersect, poly->s[inbd->j], &inbd->vp);
		vec3_crossproduct(poly->e[inbd->j], &inbd->vp, &inbd->vc);
		if (inbd->a > inbd->b)
		{
			if (vec3_dotproduct(&interinfo->normal, &inbd->vc) < 0)
				inbd->c = 0;
		}
		else if (vec3_dotproduct(&interinfo->normal, &inbd->vc) > 0)
			inbd->c = 0;
	}
	if (inbd->c == 1)
	{
		inbd->tmpdist = vec3_length(&interinfo->intersect, view);
		if (inbd->tmpdist < inbd->dist)
		{
			inbd->dist = inbd->tmpdist;
			if (inbd->a > inbd->b)
				vec3_reverse(&interinfo->normal);
			inter_cpy(&inbd->interinfo_tmp, interinfo);
		}
	}
}

static int			is_inbound(t_interinfo *interinfo, t_obj *obj, t_vec3 *view,
								t_vec3 vdir)
{
	t_inbound	inbd;

	inbd.i = -1;
	inbd.dist = 99999999;
	inbd.tmpdist = 0;
	while (++inbd.i < obj->npoly)
	{
		inbd.t = (vec3_dotproduct(&obj->poly[inbd.i]->n,
					obj->poly[inbd.i]->s[0]) -
					vec3_dotproduct(&obj->poly[inbd.i]->n, view)) /
					vec3_dotproduct(&obj->poly[inbd.i]->n, &vdir);
		if (inbd.t < 0)
			continue;
		vec3_add(view, vec3_scale(&vdir, inbd.t, MULT, &interinfo->intersect),
			&interinfo->intersect);
		vector3d(&interinfo->normal, obj->poly[inbd.i]->n.x,
					obj->poly[inbd.i]->n.y, obj->poly[inbd.i]->n.z);
		vec3_sub(&interinfo->intersect, &obj->poly[inbd.i]->n, &inbd.tmp);
		inbd.a = vec3_length(&interinfo->intersect, view);
		inbd.b = vec3_length(&inbd.tmp, view);
		inoutside(interinfo, obj->poly[inbd.i], view, &inbd);
	}
	if (inbd.dist != 99999999)
		return (inter_cpy(interinfo, &inbd.interinfo_tmp));
	return (0);
}

int					render_composed(t_interinfo *interinfo, t_vec3 *view,
								t_obj *obj, t_vec3 vdir)
{
	if (!(is_inbound(interinfo, obj, view, vdir)))
		return (0);
	return (1);
}
