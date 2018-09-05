/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vector2.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/31 17:01:33 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/04 18:40:01 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/libalgebra.h"

t_vec3	*vec3_normalize(t_vec3 *v)
{
	double mag;

	mag = vec3_magnitude(v);
	v->x /= mag;
	v->y /= mag;
	v->z /= mag;
	return (v);
}

double	vec3_length(t_vec3 *v1, t_vec3 *v2)
{
	t_vec3 v3;

	vec3_sub(v2, v1, &v3);
	return (vec3_magnitude(&v3));
}

t_vec3	*vector3d(t_vec3 *v, double x, double y, double z)
{
	v->x = x;
	v->y = y;
	v->z = z;
	return (v);
}

double	vec3_sqrlength(t_vec3 *vec)
{
	return (vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

double	vec3_dotproduct(t_vec3 *v1, t_vec3 *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}
