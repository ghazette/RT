/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   rotate.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/01 18:21:03 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 14:44:04 by rlossy      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

void	transform_composed(t_obj **obj, double mat[3][3])
{
	int i;
	int j;

	i = 0;
	while (i < (*obj)->npoly)
	{
		j = 0;
		while (j < (*obj)->poly[i]->ns)
		{
			vec3_sub((*obj)->poly[i]->s[j], &(*obj)->pos,
					(*obj)->poly[i]->s[j]);
			vec3_transform((*obj)->poly[i]->s[j], mat);
			vec3_add((*obj)->poly[i]->s[j],
					&(*obj)->pos, (*obj)->poly[i]->s[j]);
			j++;
		}
		calc_edge((*obj)->poly[i], 1);
		i++;
	}
}

void	rotate_next(t_obj **obj)
{
	double matz[3][3];

	if ((*obj)->rot.z != 0)
	{
		init_matrix(OZ_ROTATION, matz, (*obj)->rot.z);
		if ((*obj)->type == COMPOSED)
			transform_composed(obj, matz);
		else
			vec3_transform(&(*obj)->dir, matz);
	}
}

void	rotate(t_obj *obj)
{
	double matx[3][3];
	double maty[3][3];

	if (obj->rot.x != 0)
	{
		init_matrix(OX_ROTATION, matx, obj->rot.x);
		if (obj->type == COMPOSED)
			transform_composed(&obj, matx);
		else
			vec3_transform(&obj->dir, matx);
	}
	if (obj->rot.y != 0)
	{
		init_matrix(OY_ROTATION, maty, obj->rot.y);
		if (obj->type == COMPOSED)
			transform_composed(&obj, maty);
		else
			vec3_transform(&obj->dir, maty);
	}
	rotate_next(&obj);
}
