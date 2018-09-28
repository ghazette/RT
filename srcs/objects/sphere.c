/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sphere.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/06 12:13:10 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/19 12:54:04 by rlossy      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

int				render_sphere(t_interinfo *interinfo, t_vec3 *view,
	t_obj *obj, t_vec3 vdir)
{
	t_calc		sph;

	vec3_sub(view, &obj->pos, &sph.ray);
	sph.b = vec3_dotproduct(&sph.ray, &vdir);
	sph.c = vec3_sqrlength(&sph.ray) - (obj->radius * obj->radius);
	sph.delta = ((sph.b * sph.b) - sph.c);
	if (sph.delta < 0)
		return (0);
	sph.t = (-sph.b);
	if (sph.delta != 0)
	{
		sph.delta = sqrt(sph.delta);
		sph.t1 = (-sph.b + sph.delta);
		sph.t2 = (-sph.b - sph.delta);
		sph.t = (sph.t1 < sph.t2) ? sph.t : sph.t2;
	}
	if (sph.t < 0)
		return (0);
	vec3_add(view, vec3_scale(&vdir, sph.t, MULT, &interinfo->intersect),
		&interinfo->intersect);
	vec3_scale(vec3_sub(&interinfo->intersect, &obj->pos,
		&interinfo->normal), obj->radius, DIV, &interinfo->normal);
	vec3_normalize(&interinfo->normal);
	return (1);
}

static void		rotate_sphere_texture(t_obj *obj)
{
	double	mat[3][3][3];

	if (obj->rot.x != 0)
	{
		init_matrix(OX_ROTATION, mat[0], obj->rot.x);
		vec3_transform(&(obj->texture.vp), mat[0]);
	}
	if (obj->rot.y != 0)
	{
		init_matrix(OY_ROTATION, mat[1], obj->rot.y);
		vec3_transform(&(obj->texture.vp), mat[1]);
	}
	if (obj->rot.z != 0)
	{
		init_matrix(OZ_ROTATION, mat[2], obj->rot.z);
		vec3_transform(&(obj->texture.vp), mat[2]);
	}
}

void			apply_sphere_texture(t_interinfo *interinfo, t_obj *obj)
{
	vector3d(&(obj->texture.vn), 0, 1, 0);
	vector3d(&(obj->texture.ve), 1, 0, 0);
	vec3_sub(&(interinfo->intersect), &(obj->pos), &(obj->texture.vp));
	vec3_normalize(&(obj->texture.vp));
	rotate_sphere_texture(obj);
	obj->texture.phi = acos(vec3_dotproduct(&(obj->texture.vn),
	&(obj->texture.vp)));
	obj->texture.v = obj->texture.phi / PI;
	obj->texture.theta = (acos(-vec3_dotproduct(&(obj->texture.vp),
	&(obj->texture.ve)) / sin(obj->texture.phi))) / (2 * PI);
	vec3_crossproduct(&(obj->texture.vn),
					&(obj->texture.ve), &(obj->texture.res));
	if ((vec3_dotproduct(&(obj->texture.res), &(obj->texture.vp))) > 0)
		obj->texture.u = obj->texture.theta;
	else
		obj->texture.u = 1.0 - obj->texture.theta;
	obj->texture.pixel = (int)(((int)(obj->texture.u * obj->texture.width) * 4)
	+ ((int)(obj->texture.v * obj->texture.height) * (obj->texture.width * 4)));
	obj->color.x = obj->texture.data[obj->texture.pixel + 2];
	obj->color.y = obj->texture.data[obj->texture.pixel + 1];
	obj->color.z = obj->texture.data[obj->texture.pixel];
	vec3_normalizeby(&(obj->color), 255);
}
