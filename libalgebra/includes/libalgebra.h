/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libalgebra.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/30 09:27:29 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/06 14:57:50 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LIBALGEBRA_H
# define LIBALGEBRA_H
# include <math.h>
# include <string.h>
# define OX_ROTATION 0x01
# define OY_ROTATION 0x02
# define OZ_ROTATION 0x03
# define SUB 0x05
# define MULT 0x15
# define DIV 0x25
# define ADD 0x35
# define TORAD M_PI / 180

typedef struct	s_vec3
{
	double x;
	double y;
	double z;

}				t_vec3;

/*
** VECTOR 3
*/

t_vec3			*vec3_normalize(t_vec3 *v);
void			vec3_normalizeby(t_vec3 *v, double n);
double			vec3_length(t_vec3 *v1, t_vec3 *v2);
t_vec3			*vec3_add(t_vec3 *v1, t_vec3 *v2, t_vec3 *res);
t_vec3			*vec3_sub(t_vec3 *v1, t_vec3 *v2, t_vec3 *res);
t_vec3			*vec3_mult(t_vec3 *v1, t_vec3 *v2, t_vec3 *res);
double			vec3_magnitude(t_vec3 *v);
t_vec3			*vec3_crossproduct(t_vec3 *v1, t_vec3 *v2, t_vec3 *res);
t_vec3			*vec3_scale(t_vec3 *v, double nb, int sign, t_vec3 *res);
t_vec3			*vector3d(t_vec3 *v, double x, double y, double z);
double			vec3_dotproduct(t_vec3 *v1, t_vec3 *v2);
double			vec3_scalarproduct(t_vec3 *v1, double n);
double			vec3_sqrlength(t_vec3 *vec);
void			vec3_reverse(t_vec3 *v);

/*
** MATRIX 3x3
*/

void			init_matrix(int type, double mat[3][3], double angle);
void			vec3_transform(t_vec3 *vector, double mat[3][3]);

/*
** UTILS
*/

void			*ft_memset(void *b, int c, size_t n);
double			ft_reg(double x, double min, double max);

#endif
