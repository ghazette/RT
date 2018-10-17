/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   rt.h                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/01 14:35:02 by rlossy       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/03 14:10:37 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# include <time.h>
# include <math.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/stat.h>
# include <sys/types.h>
# include "keycode.h"
# include "../minilibx_macos/mlx.h"
# include "../libft/includes/libft.h"
# include "../libbmp/includes/libbmp.h"
# include "../libalgebra/includes/libalgebra.h"
# define PI 3.14159265359
# define AIR 1.0
# define MAX(a, b) (a < b ? b : a)
# define RGB mlx->rgb
# define CONE 0x103
# define CUBE 0x105
# define WIN_W 1280
# define WIN_H 960
# define LIMIT 1000
# define PLANE 0x101
# define SPHERE 0x100
# define FILTER mlx->filter
# define THREADS 8
# define REFRACT 0x108
# define CYLINDER 0x102
# define COMPOSED 0x104
# define BTNHEIGHT 40
# define SUN_POWER 80
# define NO_REFLECT 0x106
# define INTER_WIDTH 250
# define CONCAT_COLOR 0x107
# define OBJ_FROMFILE 0x200
# define MAX_ITERATION 5

typedef struct		s_filter
{
	double			gray;
	double			sepia[3];
}					t_filter;

typedef struct		s_interface
{
	int				width;
	int				offset;
	int				focus;
	int				id_select_obj;
}					t_interface;

typedef struct		s_intersectinfo
{
	t_vec3			intersect;
	t_vec3			normal;
}					t_interinfo;

typedef struct		s_material
{
	double			ambient;
	double			reflectivity;
	double			refraction;
	t_vec3			color;
	t_vec3			specular;
}					t_material;

typedef struct		s_texture
{
	int				pixel;
	double			u;
	double			v;
	double			phi;
	double			theta;
	unsigned char	*data;
	t_vec3			vn;
	t_vec3			vp;
	t_vec3			ve;
	t_vec3			res;
	size_t			width;
	size_t			height;
}					t_texture;

typedef struct		s_poly
{
	int				ns;
	t_vec3			**s;
	t_vec3			**e;
	t_vec3			n;
}					t_poly;

typedef struct		s_obj
{
	int				id;
	int				type;
	int				form;
	int				width;
	int				depth;
	int				npoly;
	int				height;
	int				havenormal;
	char			*name;
	double			radius;
	t_poly			**poly;
	t_vec3			pos;
	t_vec3			dir;
	t_vec3			rot;
	t_vec3			color;
	t_texture		texture;
	t_material		material;
	int				(*render_func)(t_interinfo *interinfo, t_vec3 *view,
		struct s_obj*, t_vec3);
}					t_obj;

typedef struct		s_cam
{
	int				res[2];
	double			x_indent;
	double			y_indent;
	double			viewplane_dist;
	double			viewplane_width;
	double			viewplane_height;
	t_vec3			pos;
	t_vec3			rot;
	t_vec3			npos;
	t_vec3			lookat;
	t_vec3			up_vec;
	t_vec3			dir_vec;
	t_vec3			right_vec;
	t_vec3			viewplaneupleft_vec;
}					t_cam;

typedef struct		s_spot
{
	int				id;
	char			*name;
	t_vec3			pos;
	t_vec3			color;
	t_material		material;
}					t_spot;

typedef struct		s_scene
{
	int				light;
	int				nb_obj;
	int				nb_spot;
	char			*name;
	t_obj			**objs;
	t_cam			*cam;
	t_spot			**spot;
	t_interinfo		*interinfo;
}					t_sce;

typedef struct		s_mlx
{
	int				i;
	int				id;
	int				ed;
	int				th;
	int				bpp;
	int				aax;
	int				aay;
	int				line;
	int				aaoff;
	int				effect;
	int				line_cnt;
	char			*pixel_img;
	void			*mlx;
	void			*win;
	void			*img;
	double			p;
	double			aa;
	double			reg;
	double			ambient;
	t_sce			*scene;
	t_vec3			rgb;
	t_vec3			vdir;
	t_filter		filter;
	t_interface		*interf;
}					t_mlx;

typedef struct		s_calc
{
	double			a;
	double			b;
	double			c;
	double			delta;
	double			t;
	double			t1;
	double			t2;
	double			val[3];
	double			angle;
	t_vec3			ray;
}					t_calc;

typedef struct		s_phong
{
	int				is_shadow;
	int				rm_specular;
	t_obj			*obj;
	t_spot			*spot;
	t_vec3			vdir;
	t_vec3			*normal;
	t_vec3			*light_vec;
	t_material		material;
}					t_phong;

typedef struct		s_inbound
{
	int				c;
	int				i;
	int				j;
	double			t;
	double			a;
	double			b;
	double			dist;
	double			tmpdist;
	t_vec3			vp;
	t_vec3			vc;
	t_vec3			tmp;
	t_interinfo		interinfo_tmp;
}					t_inbound;

typedef struct		s_cube
{
	int				index[4];
	double			x;
	double			y;
	double			z;
	double			h;
	double			w;
	double			d;
	t_vec3			p[8];
}					t_cube;

typedef struct		s_fetch
{
	int				i[2];
	char			*line;
	char			**split;
}					t_fetch;

/*
** GENERAL
*/

int					obj_cpy(t_sce *scene, t_sce *src);
int					inter_cpy(t_interinfo *dest, t_interinfo *src);
int					intersect(t_mlx *mlx, t_vec3 *view, t_vec3 vdir);
char				*rand_string(int len);
void				usage(void);
void				reset(t_phong *phong, t_mlx *mlxfree, t_mlx *mlxreset);
void				render(t_mlx *mlx);
void				rotate(t_obj *obj);
void				free_mlx(t_mlx *mlx);
void				ft_average(t_mlx *mlx, t_vec3 *reg, double coeff);
void				init_camera(t_mlx *mlx);
void				draw_point(int x, int y, t_mlx *mlx, int color);
void				view_correction(t_mlx *mlx, t_vec3 *view, int type);
t_mlx				*mlx_cpy(t_mlx *src);
t_mlx				*mlx_init_all(char *window_name);
t_vec3				*calc_dir_vec(t_mlx *mlx, t_vec3 *vdir, double x, double y);

/*
** Visual Effects
*/

void				ft_effect(t_mlx *mlx, int effect);
void				ft_reflect(t_mlx *mlx, double *coeff);
void				ft_refract(t_mlx *mlx);
int					is_refract(t_mlx *mlx);

/*
** OBJECT RENDER
*/

int					render_cylinder(t_interinfo *interinfo, t_vec3 *view,
						t_obj *obj, t_vec3 vdir);
int					render_sphere(t_interinfo *interinfo, t_vec3 *view,
						t_obj *obj, t_vec3 vdir);
int					render_plane(t_interinfo *interinfo, t_vec3 *view,
						t_obj *obj, t_vec3 vdir);
int					render_cone(t_interinfo *interinfo, t_vec3 *view,
						t_obj *obj, t_vec3 vdir);
int					render_composed(t_interinfo *interinfo, t_vec3 *view,
						t_obj *obj, t_vec3 vdir);

/*
** PARSING
*/

int					init_vec(t_vec3 *pos, char **data);
int					check_dir(char *fn);
int					open_file(t_mlx *mlx, char *fn);
int					check_file(char *fn);
int					fetch_data(t_mlx *mlx, int fd);
int					ft_parser_secure(char *line, char ***split);

/*
** FETCHING
*/

int					get_nb_obj(char *fn, int ret[2]);
int					fetch_spot(t_mlx *mlx, t_spot **spot, int fd);
int					new_camera(t_mlx *mlx);
int					type_define(char *type, t_obj *obj);
int					form_define(char *form, t_obj *obj);
int					check_object(int *aaoff, t_obj *obj);
int					fetch_camera(t_mlx *mlx, int fd);
int					fetch_object(t_mlx *mlx, int fd);
int					fetch_spot_array_help(t_spot *spot, char **split);
t_obj				*new_object();
t_spot				*new_spot();

/*
** LIGHT
*/

void				phong_calc(t_phong *phong);
void				phong_calcfinal(t_phong *phong, int nbspot);
void				light_intersect(t_mlx *mlx, t_obj *obj, t_spot *spot,
						t_phong *phong);

/*
** INTERFACE
*/

int					display_spot(t_mlx *mlx, t_spot *obj, char *str, int y);
int					inter_select_up(t_mlx *mlx);
int					display_interface(t_mlx *mlx);
int					inter_select_down(t_mlx *mlx);
char				*get_type(int type);
char				*parse_vec(t_vec3 v);
void				display_focus(t_mlx *mlx);
void				display_camera(t_mlx *mlx);
void				export_button(t_mlx *mlx, int color);
void				clear_interface(t_mlx *mlx);

/*
** INPUT
*/

int					key_func(int key, void *p);
int					mouse_func(int button, int x, int y, t_mlx *mlx);
int					motion_func(int x, int y, t_mlx *mlx);
void				key_up(t_mlx *mlx, t_interface *interf);
void				mv_cmp(t_obj **obj, char c, int sign);
void				key_rot(t_mlx *mlx, int key);
void				key_down(t_mlx *mlx, t_interface *interf);
void				key_left(t_mlx *mlx, t_interface *interf);
void				key_right(t_mlx *mlx, t_interface *interf);
void				scroll_up(t_mlx *mlx, int x, int y);
void				left_click(t_mlx *mlx, int x, int y);
void				scroll_down(t_mlx *mlx, int x, int y);

/*
** TEXTURE
*/

void				apply_sphere_texture(t_interinfo *interinfo, t_obj *obj);

/*
**	.obj PARSER
*/

int					fetch_obj(char *path, t_obj **obj);
int					calc_cube(t_obj *obj);
int					calc_edge(t_poly *poly, int calcnormal, int realloc);
int					get_obj_data(char *path, int *vertex, int *normal,
									int *face);
int					get_obj_normal(int fd, int normal, t_obj **obj,
									t_vec3 ***n);
int					get_obj_vertex(int fd, int vertex, t_obj **obj,
									t_vec3 ***s);
void				free_poly(t_obj *obj);
void				free_polydata(const int *cnt, t_vec3 ***polydata);
void				ft_calc_edge_normal(t_poly *poly);

#endif
