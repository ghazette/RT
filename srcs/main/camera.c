/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   camera.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/31 17:07:53 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/24 12:51:03 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rt.h"

void		init_camera(t_mlx *mlx)
{
	t_cam	*cam;
	t_vec3	res[3];
	double	mat[3][3][3];

	cam = mlx->scene->cam;
	cam->viewplane_width = 1;
	cam->viewplane_height = 0.7;
	vector3d(&cam->up_vec, 0, 1, 0);
	init_matrix(OZ_ROTATION, mat[0], cam->rot.z);
	vec3_transform(&cam->up_vec, mat[0]);
	vec3_sub(&cam->lookat, &cam->pos, &cam->dir_vec);
	init_matrix(OY_ROTATION, mat[1], cam->rot.y);
	vec3_transform(&cam->dir_vec, mat[1]);
	init_matrix(OX_ROTATION, mat[2], cam->rot.x);
	vec3_transform(&cam->dir_vec, mat[2]);
	vec3_normalize(&cam->dir_vec);
	vec3_crossproduct(&cam->up_vec, &cam->dir_vec, &cam->right_vec);
	vec3_crossproduct(&cam->dir_vec, &cam->right_vec, &cam->up_vec);
	vec3_add(&cam->pos, vec3_sub(vec3_add(vec3_scale(&cam->dir_vec,
	cam->viewplane_dist, MULT, &res[0]), vec3_scale(&cam->up_vec,
	cam->viewplane_height / 2.00, MULT, &res[1]), &cam->viewplaneupleft_vec),
	vec3_scale(&cam->right_vec, cam->viewplane_width / 2.00, MULT, &res[2]),
	&cam->viewplaneupleft_vec), &cam->viewplaneupleft_vec);
	cam->x_indent = cam->viewplane_width / (double)WIN_W;
	cam->y_indent = cam->viewplane_height / (double)WIN_H;
}

t_vec3		*calc_dir_vec(t_mlx *mlx, t_vec3 *vdir, double x, double y)
{
	t_cam	*cam;
	t_vec3	res[4];

	cam = mlx->scene->cam;
	vec3_sub(vec3_sub(vec3_add(&cam->viewplaneupleft_vec,
	vec3_scale(vec3_scale(&cam->right_vec, cam->x_indent,
		MULT, &res[1]), x, MULT, &res[0]), vdir),
	vec3_scale(vec3_scale(&cam->up_vec, cam->y_indent,
		MULT, &res[2]), y, MULT, &res[3]), vdir),
	&cam->pos, vdir);
	vec3_normalize(vdir);
	return (vdir);
}
