/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   phong.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/06 16:17:44 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/11 15:58:15 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	phong_calc(t_phong *phong)
{
	t_vec3		res;
	t_vec3		h;
	t_material	material;
	double		v;

	v = MAX(vec3_dotproduct(phong->normal, phong->light_vec), 0);
	vec3_scale(&phong->obj->color, v, MULT, &res);
	vec3_mult(&phong->spot->color, &res, &material.color);
	if (phong->is_shadow)
		vec3_scale(&material.color, 3.0, DIV, &material.color);
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
	if (phong->material.color.x >= 1.0)
		phong->material.color.x = 1.0;
	if (phong->material.color.y >= 1.0)
		phong->material.color.y = 1.0;
	if (phong->material.color.z >= 1.0)
		phong->material.color.z = 1.0;
	phong->fcolor.rgb[2] = phong->material.color.x * 255;
	phong->fcolor.rgb[1] = phong->material.color.y * 255;
	phong->fcolor.rgb[0] = phong->material.color.z * 255;
}
