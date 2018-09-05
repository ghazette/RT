/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   matrix.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/30 10:53:06 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/01 18:23:23 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/libalgebra.h"

static void	init_ox_rotation(double mat[3][3], double angle)
{
	double a;
	double b;

	a = cos(angle);
	b = sin(angle);
	mat[0][0] = 1;
	mat[1][1] = a;
	mat[2][2] = a;
	mat[1][2] = -b;
	mat[2][1] = b;
}

static void	init_oy_rotation(double mat[3][3], double angle)
{
	double a;
	double b;

	a = cos(angle);
	b = sin(angle);
	mat[0][0] = a;
	mat[1][1] = 1;
	mat[2][2] = a;
	mat[2][0] = -b;
	mat[0][2] = b;
}

static void	init_oz_rotation(double mat[3][3], double angle)
{
	double a;
	double b;

	a = cos(angle);
	b = sin(angle);
	mat[0][0] = a;
	mat[1][1] = a;
	mat[2][2] = 1;
	mat[1][0] = b;
	mat[0][1] = -b;
}

/*
** fill the matrix[3][3] with the specificed rotation angle
*/

void		init_matrix(int type, double mat[3][3], double angle)
{
	angle *= TORAD;
	ft_memset(mat, 0, sizeof(double) * 9);
	if (type == OX_ROTATION)
		init_ox_rotation(mat, angle);
	if (type == OY_ROTATION)
		init_oy_rotation(mat, angle);
	if (type == OZ_ROTATION)
		init_oz_rotation(mat, angle);
}

/*
** Multiply the vec by the specified matrix
*/

void		vec3_transform(t_vec3 *vec, double mat[3][3])
{
	t_vec3 tmp;

	tmp.x = vec->x * mat[0][0] + vec->y * mat[0][1] + vec->z * mat[0][2];
	tmp.y = vec->x * mat[1][0] + vec->y * mat[1][1] + vec->z * mat[1][2];
	tmp.z = vec->x * mat[2][0] + vec->y * mat[2][1] + vec->z * mat[2][2];
	vec->x = tmp.x;
	vec->y = tmp.y;
	vec->z = tmp.z;
}
