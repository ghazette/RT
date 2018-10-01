/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   phong.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/06 16:17:44 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/27 11:51:28 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rt.h"

void	phong_calc(t_phong *phong)
{
	double		v;
	t_vec3		res;
	t_vec3		h;
	t_material	material;

	v = MAX(vec3_dotproduct(phong->normal, phong->light_vec), 0);
	vec3_scale(&phong->obj->color, v, MULT, &res);
	vec3_mult(&phong->spot->color, &res, &material.color);
	if (phong->is_shadow)
		vec3_scale(&material.color, 2, DIV, &material.color);
	vec3_add(&phong->material.color, &material.color, &phong->material.color);
	if (!phong->is_shadow)
	{
		vec3_add(&phong->vdir, phong->light_vec, &h);
		vec3_normalize(&h);
		v = pow(vec3_dotproduct(phong->normal, &h), SUN_POWER);
		vec3_scale(&phong->obj->material.specular, MAX(v, 0), MULT, &res);
		vec3_mult(&phong->spot->material.specular, &res, &material.specular);
		vec3_add(&phong->material.specular, &material.specular,
			&phong->material.specular);
	}
	phong->material.ambient += (phong->material.ambient == 0) ?
	phong->spot->material.ambient + phong->obj->material.ambient :
	phong->spot->material.ambient;
}

void	phong_calcfinal(t_phong *phong, int nbspot)
{
	vec3_scale(&phong->material.color, nbspot, DIV, &phong->material.color);
	vec3_scale(&phong->material.specular, nbspot, DIV,
				&phong->material.specular);
	phong->material.ambient /= nbspot;
	if (!phong->rm_specular)
		vec3_add(&phong->material.color, &phong->material.specular,
				&phong->material.color);
	vec3_scale(&phong->material.color, phong->material.ambient, ADD,
				&phong->material.color);
	phong->material.color.x = pow(phong->material.color.x, 1.0);
	phong->material.color.y = pow(phong->material.color.y, 1.0);
	phong->material.color.z = pow(phong->material.color.z, 1.0);
}
