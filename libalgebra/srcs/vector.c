/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vector.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/23 17:19:07 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/05/30 09:27:00 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/libalgebra.h"
#include <stdlib.h>

t_vec3	*vec3_add(t_vec3 *v1, t_vec3 *v2, t_vec3 *res)
{
	res->x = v1->x + v2->x;
	res->y = v1->y + v2->y;
	res->z = v1->z + v2->z;
	return (res);
}

t_vec3	*vec3_sub(t_vec3 *v1, t_vec3 *v2, t_vec3 *res)
{
	res->x = v1->x - v2->x;
	res->y = v1->y - v2->y;
	res->z = v1->z - v2->z;
	return (res);
}

double	vec3_magnitude(t_vec3 *v)
{
	return (sqrt((v->x * v->x) + (v->y * v->y) + (v->z * v->z)));
}

t_vec3	*vec3_crossproduct(t_vec3 *v1, t_vec3 *v2, t_vec3 *res)
{
	res->x = (v1->y * v2->z) - (v1->z * v2->y);
	res->y = (v1->z * v2->x) - (v1->x * v2->z);
	res->z = (v1->x * v2->y) - (v1->y * v2->x);
	return (res);
}

t_vec3	*vec3_scale(t_vec3 *v, double nb, int sign, t_vec3 *res)
{
	if (sign == DIV)
	{
		res->x = v->x / nb;
		res->y = v->y / nb;
		res->z = v->z / nb;
	}
	if (sign == MULT)
	{
		res->x = v->x * nb;
		res->y = v->y * nb;
		res->z = v->z * nb;
	}
	if (sign == SUB)
	{
		res->x = v->x - nb;
		res->y = v->y - nb;
		res->z = v->z - nb;
	}
	if (sign == ADD)
	{
		res->x = v->x + nb;
		res->y = v->y + nb;
		res->z = v->z + nb;
	}
	return (res);
}
