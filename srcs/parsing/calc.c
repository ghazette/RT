/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   calc.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlossy <rlossy@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/01 12:33:11 by rlossy       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/01 14:33:54 by rlossy      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rt.h"

static t_poly	*new_poly(t_poly *poly, int ns, t_vec3 *p, int *index)
{
	int i;

	i = -1;
	if (!(poly = malloc(sizeof(t_poly))))
		return (poly);
	poly->ns = ns;
	poly->s = malloc(sizeof(t_vec3*) * ns);
	while (++i < ns)
	{
		if (!(poly->s[i] = malloc(sizeof(t_vec3))))
			return (poly);
		poly->s[i] = vector3d(poly->s[i], p[index[i]].x, p[index[i]].y,
								p[index[i]].z);
	}
	calc_edge(poly, 1, 1);
	return (poly);
}

int				calc_edge(t_poly *poly, int calcnormal, int realloc)
{
	int		i;

	i = 0;
	if (realloc)
		if (!(poly->e = malloc(sizeof(t_vec3*) * poly->ns)))
			return (0);
	while (++i < poly->ns)
	{
		if (realloc)
			if (!(poly->e[i - 1] = malloc(sizeof(t_vec3))))
				return (0);
		vec3_sub(poly->s[i - 1], poly->s[i], poly->e[i - 1]);
	}
	if (realloc)
		if (!(poly->e[i - 1] = malloc(sizeof(t_vec3))))
			return (0);
	poly->e[i - 1] = vec3_sub(poly->s[i - 1], poly->s[0], poly->e[i - 1]);
	if (calcnormal)
		ft_calc_edge_normal(poly);
	return (1);
}

static void		calc_faces(t_cube *cube, int face)
{
	cube->index[0] = (face == 0) ? 0 : cube->index[0];
	cube->index[1] = (face == 0) ? 1 : cube->index[1];
	cube->index[2] = (face == 0) ? 2 : cube->index[2];
	cube->index[3] = (face == 0) ? 3 : cube->index[3];
	cube->index[0] = (face == 1) ? 1 : cube->index[0];
	cube->index[1] = (face == 1) ? 5 : cube->index[1];
	cube->index[2] = (face == 1) ? 6 : cube->index[2];
	cube->index[3] = (face == 1) ? 2 : cube->index[3];
	cube->index[0] = (face == 2) ? 5 : cube->index[0];
	cube->index[1] = (face == 2) ? 4 : cube->index[1];
	cube->index[2] = (face == 2) ? 7 : cube->index[2];
	cube->index[3] = (face == 2) ? 6 : cube->index[3];
	cube->index[0] = (face == 3) ? 0 : cube->index[0];
	cube->index[1] = (face == 3) ? 3 : cube->index[1];
	cube->index[2] = (face == 3) ? 7 : cube->index[2];
	cube->index[3] = (face == 3) ? 4 : cube->index[3];
	cube->index[0] = (face == 4) ? 0 : cube->index[0];
	cube->index[1] = (face == 4) ? 4 : cube->index[1];
	cube->index[2] = (face == 4) ? 5 : cube->index[2];
	cube->index[3] = (face == 4) ? 1 : cube->index[3];
	cube->index[0] = (face == 5) ? 3 : cube->index[0];
	cube->index[1] = (face == 5) ? 2 : cube->index[1];
	cube->index[2] = (face == 5) ? 6 : cube->index[2];
	cube->index[3] = (face == 5) ? 7 : cube->index[3];
}

static void		calc_vecs(t_cube *cube)
{
	vector3d(&cube->p[0], cube->x - cube->w, cube->y + cube->h,
				cube->z - cube->d);
	vector3d(&cube->p[1], cube->x + cube->w, cube->y + cube->h,
				cube->z - cube->d);
	vector3d(&cube->p[2], cube->x + cube->w, cube->y - cube->h,
				cube->z - cube->d);
	vector3d(&cube->p[3], cube->x - cube->w, cube->y - cube->h,
				cube->z - cube->d);
	vector3d(&cube->p[4], cube->x - cube->w, cube->y + cube->h,
				cube->z + cube->d);
	vector3d(&cube->p[5], cube->x + cube->w, cube->y + cube->h,
				cube->z + cube->d);
	vector3d(&cube->p[6], cube->x + cube->w, cube->y - cube->h,
				cube->z + cube->d);
	vector3d(&cube->p[7], cube->x - cube->w, cube->y - cube->h,
				cube->z + cube->d);
}

int				calc_cube(t_obj *obj)
{
	t_cube	cube;

	cube.x = obj->pos.x;
	cube.y = obj->pos.y;
	cube.z = obj->pos.z;
	cube.h = (double)obj->height / 2;
	cube.w = (double)obj->width / 2;
	cube.d = (double)obj->depth / 2;
	calc_vecs(&cube);
	obj->poly = malloc(sizeof(t_poly*) * obj->npoly);
	calc_faces(&cube, 0);
	obj->poly[0] = new_poly(obj->poly[0], 4, cube.p, cube.index);
	calc_faces(&cube, 1);
	obj->poly[1] = new_poly(obj->poly[1], 4, cube.p, cube.index);
	calc_faces(&cube, 2);
	obj->poly[2] = new_poly(obj->poly[2], 4, cube.p, cube.index);
	calc_faces(&cube, 3);
	obj->poly[3] = new_poly(obj->poly[3], 4, cube.p, cube.index);
	calc_faces(&cube, 4);
	obj->poly[4] = new_poly(obj->poly[4], 4, cube.p, cube.index);
	calc_faces(&cube, 5);
	obj->poly[5] = new_poly(obj->poly[5], 4, cube.p, cube.index);
	return (1);
}
