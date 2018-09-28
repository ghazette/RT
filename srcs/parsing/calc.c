/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fetch.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/06 12:08:00 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/27 16:48:45 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

int		calc_edge(t_poly *poly, int calcnormal)
{
	int i;
	t_vec3 v0;
	t_vec3 v1;

	i = 1;
	poly->e = malloc(sizeof(t_vec3*) * poly->ns);
	while (i < poly->ns)
	{
		poly->e[i - 1] = malloc(sizeof(t_vec3));
		vec3_sub(poly->s[i - 1], poly->s[i], poly->e[i - 1]);
		i++;
	}
	poly->e[i - 1] = malloc(sizeof(t_vec3));
	poly->e[i - 1] = vec3_sub(poly->s[i - 1], poly->s[0], poly->e[i - 1]);
	if (calcnormal)
	{
		vec3_sub(poly->e[1], poly->e[0], &v0);
		vec3_sub(poly->e[2], poly->e[0], &v1);
		vec3_crossproduct(&v0, &v1, &poly->n);
		vec3_normalize(&poly->n);
	}
	return (1);
}

int		calc_cube(t_obj *obj)
{
	int i;
	int j;
	double x;
	double y;
	double z;

	double h;
	double w;
	double d;
	t_vec3 p[8];
	int index[4];


	x = obj->pos.x;
	y = obj->pos.y;
	z = obj->pos.z;
	h = (double)obj->height / 2;
	w = (double)obj->width / 2;
	d = (double)obj->depth / 2;
	vector3d(&p[0], x - w, y + h, z - d);
	vector3d(&p[1], x + w, y + h, z - d);
	vector3d(&p[2], x + w, y - h, z - d);
	vector3d(&p[3], x - w, y - h, z - d);
	vector3d(&p[4], x - w, y + h, z + d);
	vector3d(&p[5], x + w, y + h, z + d);
	vector3d(&p[6], x + w, y - h, z + d);
	vector3d(&p[7], x - w, y - h, z + d);
	obj->poly = malloc(sizeof(t_poly*) * obj->npoly);
	index[0] = 0;
	index[1] = 1;
	index[2] = 2;
	index[3] = 3;
	obj->poly[0] = new_poly(obj->poly[0], 4, p, index);
	index[0] = 1;
	index[1] = 5;
	index[2] = 6;
	index[3] = 2;
	obj->poly[1] = new_poly(obj->poly[1], 4, p, index);
	index[0] = 5;
	index[1] = 4;
	index[2] = 7;
	index[3] = 6;
	obj->poly[2] = new_poly(obj->poly[2], 4, p, index);
	index[0] = 0;
	index[1] = 3;
	index[2] = 7;
	index[3] = 4;
	obj->poly[3] = new_poly(obj->poly[3], 4, p, index);
	index[0] = 0;
	index[1] = 4;
	index[2] = 5;
	index[3] = 1;
	obj->poly[4] = new_poly(obj->poly[4], 4, p, index);
	index[0] = 3;
	index[1] = 2;
	index[2] = 6;
	index[3] = 7;
	obj->poly[5] = new_poly(obj->poly[5], 4, p, index);
	return (1);
}
