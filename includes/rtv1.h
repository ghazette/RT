/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   rtv1.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/20 14:58:40 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/06 11:35:51 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include "../minilibx_macos/mlx.h"
# include "../libalgebra/includes/libalgebra.h"
# include "../libft/includes/libft.h"
# include "../libbmp/includes/libbmp.h"
# include <pthread.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <time.h>
# define PI 3.14159265359
# define MAX(A, B) (A < B ? B : A)
# define DEGTORAD(DEG) (DEG * PI / 180)
# define WIN_W 1280
# define WIN_H 960
# define INTER_WIDTH 250
# define SPHERE 0x100
# define PLANE 0x101
# define CYLINDER 0x102
# define CONE 0x103
# define BTNHEIGHT 40
# define SUN_POWER 80
# define THREADS 8

typedef struct		s_interface
{
	int				width;
	int				focus;
	int				offset;
	int				id_select_obj;
}					t_interface;

typedef struct		s_intersectinfo
{
	t_vec3			normal;
	t_vec3			intersect;
}					t_interinfo;

typedef union		u_color
{
	unsigned int	hex;
	unsigned char	rgb[4];
}					t_color;

typedef struct		s_material
{
	double			ambient;
	t_vec3			color;
	t_vec3			specular;
}					t_material;

typedef struct		s_shape
{
	int				len;
	t_vec3			v0;
	t_vec3			v1;
	t_vec3			v2;
	t_vec3			v3;
	t_vec3			e0;
	t_vec3			e1;
}					t_shape;

typedef struct		s_obj
{
	int				id;
	int				type;
	char			*name;
	double			radius;
	t_vec3			pos;
	t_vec3			dir;
	t_vec3			rot;
	t_vec3			color;
	t_material		material;
	t_shape			shape;
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
	t_vec3			dir_vec;
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
	int				ed;
	int				bpp;
	int				line;
	int				endx;
	int				endy;
	int				startx;
	int				starty;
	int				line_cnt;
	void			*mlx;
	void			*win;
	void			*img;
	char			*pixel_img;
	t_sce			*scene;
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
	int				rm_specular;
	double			is_shadow;
	t_obj			*obj;
	t_spot			*spot;
	t_vec3			vdir;
	t_vec3			*normal;
	t_vec3			*light_vec;
	t_color			fcolor;
	t_material		material;
}					t_phong;

typedef struct		s_rt
{
	int				id;
	int				i;
	int				savex;
	t_mlx			*mlx;
	t_vec3			vdir;
}					t_rt;

/*
** GENERAL
*/

int					get_thread_number(char *th);
char				*rand_string(int len);
void				init_camera(t_mlx *mlx);
void				draw_point(int x, int y, t_mlx *mlx, unsigned char *color);
void				render(t_mlx *mlx);
void				usage(void);
void				inter_cpy(t_interinfo *dest, t_interinfo *src);
void				rotate(t_obj *obj);
double				is_sphere(t_obj *obj, t_vec3 *c2);
t_mlx				*mlx_cpy(t_mlx *src);
t_mlx				*mlx_init_all(char *window_name);
t_vec3				*calc_dir_vec(t_mlx *mlx, t_vec3 *vdir, double x, double y);

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

/*
** PARSING
*/

int					open_file(t_mlx *mlx, char *fn);
int					init_vec(t_vec3 *pos, char **data);
int					init_color(t_color *color, char **data);
int					check_file(char *fn);
int					check_dir(char *fn);

/*
** FETCHING
*/

int					get_nb_obj(char *fn, int ret[2]);
int					fetch_camera(t_mlx *mlx, int fd);
int					fetch_object(t_mlx *mlx, int fd);
int					fetch_spot(t_mlx *mlx, t_spot **spot, int fd);
int					new_camera(t_mlx *mlx);
t_obj				*new_object();
t_spot				*new_spot();

/*
** LIGHT
*/

void				phong_calcfinal(t_phong *phong, int nbspot);
void				phong_calc(t_phong *phong);
void				light_intersect(t_mlx *mlx, t_obj *obj, t_spot *spot,
						t_phong *phong);

/*
** INTERFACE
*/

int					display_interface(t_mlx *mlx);
int					display_spot(t_mlx *mlx, t_spot *obj, char *str, int y);
int					inter_select_up(t_mlx *mlx);
int					inter_select_down(t_mlx *mlx);
char				*get_type(int type);
char				*parse_vec(t_vec3 v);
void				display_focus(t_mlx *mlx);
void				clear_interface(t_mlx *mlx);
void				export_button(t_mlx *mlx, int color);

/*
** INPUT
*/

int					mouse_func(int button, int x, int y, t_mlx *mlx);
int					motion_func(int x, int y, t_mlx *mlx);
int					key_func(int key, void *p);
int					export_scene(t_mlx *mlx);
void				left_click(t_mlx *mlx, int x, int y);
void				scroll_up(t_mlx *mlx, int x, int y);
void				scroll_down(t_mlx *mlx, int x, int y);
void				key_up(t_mlx *mlx);
void				key_down(t_mlx *mlx);
void				key_right(t_mlx *mlx);
void				key_left(t_mlx *mlx);
void				key_rot(t_mlx *mlx, int key);

#endif
