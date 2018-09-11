/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vector3.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/11 09:30:33 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/06 15:33:57 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/libalgebra.h"

void	vec3_reverse(t_vec3 *v)
{
	v->x = -v->x;
	v->y = -v->y;
	v->z = -v->z;
}

double	vec3_scalarproduct(t_vec3 *v1, double n)
{
	return (v1->x * n + v1->y * n + v1->z * n);
}

t_vec3	*vec3_mult(t_vec3 *v1, t_vec3 *v2, t_vec3 *res)
{
	res->x = v1->x * v2->x;
	res->y = v1->y * v2->y;
	res->z = v1->z * v2->z;
	return (res);
}

void	vec3_normalizeby(t_vec3 *v, double n)
{
	v->x /= n;
	v->y /= n;
	v->z /= n;
}

double	ft_reg(double x, double min, double max)
{
	x = x < min ? min : x;
	x = x > max ? max : x;
	return (x);
}