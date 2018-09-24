/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   rotate.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/01 18:21:03 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/11 13:17:50 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rtv1.h"


void	rotate(t_obj *obj)
{
	double matz[3][3];
	double matx[3][3];
	double maty[3][3];
	int i = 0;
	int j = 0;

	if (obj->rot.x != 0)
	{
		init_matrix(OX_ROTATION, matx, obj->rot.x);
		if(obj->type == COMPOSED)
		{
			while (i < obj->npoly)
			{
				j = 0;
				while (j < obj->poly[i]->ns)
				{
					vec3_transform(obj->poly[i]->s[j], matx);
					j++;
				}
				vec3_transform(&obj->poly[i]->n, matx);
				i++;
			}
		}
		else
			vec3_transform(&obj->dir, matx);
	}
	if (obj->rot.y != 0)
	{
		init_matrix(OY_ROTATION, maty, obj->rot.y);
		if(obj->type == COMPOSED)
		{
			while (i < obj->npoly)
			{
				j = 0;
				while (j < obj->poly[i]->ns)
				{
					vec3_transform(obj->poly[i]->s[j], maty);
					j++;
				}
				vec3_transform(&obj->poly[i]->n, maty);
				i++;
			}
		}
		else
			vec3_transform(&obj->dir, maty);
	}
	if (obj->rot.z != 0)
	{
		init_matrix(OZ_ROTATION, matz, obj->rot.z);
		if(obj->type == COMPOSED)
		{
			while (i < obj->npoly)
			{
				j = 0;
				while (j < obj->poly[i]->ns)
				{
					vec3_transform(obj->poly[i]->s[j], matz);
					j++;
				}
				vec3_transform(&(obj)->poly[i]->n, matz);
				i++;
			}
		}
		else
			vec3_transform(&(obj)->dir, matz);
	}
}
