/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   rotate.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/01 18:21:03 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/10 17:12:28 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	rotate(t_obj *obj)
{
	double matz[3][3];
	double matx[3][3];
	double maty[3][3];

	if (obj->type != SPHERE)
	{
		if (obj->rot.x != 0)
		{
			init_matrix(OX_ROTATION, matx, obj->rot.x);
			vec3_transform(&obj->dir, matx);
		}
		if (obj->rot.y != 0)
		{
			init_matrix(OY_ROTATION, maty, obj->rot.y);
			vec3_transform(&obj->dir, maty);
		}
		if (obj->rot.z != 0)
		{
			init_matrix(OZ_ROTATION, matz, obj->rot.z);
			vec3_transform(&obj->dir, matz);
		}
	}
}
