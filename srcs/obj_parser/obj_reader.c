/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   obj_reader.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/07 13:03:47 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/19 12:46:10 by rlossy      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

static int		calc_edge(t_poly *poly)
{
	int i;

	i = 1;
	while (poly->s[i] != 0)
	{
		poly->e[i - 1] = malloc(sizeof(t_vec3));
		poly->e[i - 1] = vec3_sub(poly->s[i - 1], poly->s[i], poly->e[i - 1]);
		i++;
	}
	poly->e[i - 1] = malloc(sizeof(t_vec3));
	vec3_sub(poly->s[i - 1], poly->s[0], poly->e[i - 1]);
	poly->e[i] = 0;
	return (1);
}

static int		prep_poly(t_obj **obj)
{
	int i;

	i = 0;
	while ((*obj)->poly[i] != 0)
	{
		calc_edge((*obj)->poly[i]);
		i++;
	}
	return (1);
}

int				get_obj_data(char *path, int *vertex, int *normal, int *face)
{
	int		fd;
	char	*line;

	line = NULL;
	if ((fd = open(path, O_RDONLY)) < 0)
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 'v' && line[1] == ' ')
			(*vertex)++;
		if (line[0] == 'f' && line[1] == ' ')
			(*face)++;
		if (line[0] == 'v' && line[1] == 'n')
			(*normal)++;
		ft_strdel(&line);
	}
	if (*face == 0 || *normal == 0 || *vertex == 0)
		return (0);
	close(fd);
	return (1);
}

int				get_obj_vertex(int fd, int vertex, t_obj **obj)
{
	int		i;
	char	*line;
	char	**split;

	i = 0;
	line = NULL;
	if (!((*obj)->s = (t_vec3**)malloc(sizeof(t_vec3*) * (vertex + 1))))
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 'v' && line[1] == ' ')
		{
			if (!(split = ft_strsplit(line, ' ')))
				return (0);
			if (!((*obj)->s[i] = malloc(sizeof(t_vec3))))
				return (0);
			vector3d((*obj)->s[i], ft_atof(split[1]), ft_atof(split[2]),
					ft_atof(split[3]));
			ft_strdel(&line);
			ft_free2d(&split);
			i++;
		}
		if (i == vertex)
			break ;
	}
	(*obj)->s[vertex] = 0;
	return (1);
}

int				get_obj_normal(int fd, int normal, t_obj **obj)
{
	int		i;
	char	*line;
	char	**split;

	i = 0;
	line = NULL;
	if (!((*obj)->n = (t_vec3**)malloc(sizeof(t_vec3*) * (normal + 1))))
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 'v' && line[1] == 'n')
		{
			if (!(split = ft_strsplit(line, ' ')))
				return (0);
			if (!((*obj)->n[i] = malloc(sizeof(t_vec3))))
				return (0);
			vector3d((*obj)->n[i], ft_atof(split[1]), ft_atof(split[2]),
					ft_atof(split[3]));
			ft_strdel(&line);
			ft_free2d(&split);
			i++;
		}
		if (i == normal)
			break ;
	}
	(*obj)->n[normal] = 0;
	return (1);
}

int				set_obj_face(int fd, int face, t_obj **obj)
{
	int		i;
	int		j;
	int		slen;
	char	*line;
	char	**split2;
	char	**split;

	i = 0;
	line = NULL;
	if (!((*obj)->poly = (t_poly**)malloc(sizeof(t_poly*) * (face + 1))))
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 'f' && line[1] == ' ')
		{
			if (!(split = ft_strsplit(line, ' ')))
				return (0);
			if (!((*obj)->poly[i] = malloc(sizeof(t_poly))))
				return (0);
			slen = ft_heightlen(split);
			if (!((*obj)->poly[i]->s = (t_vec3**)malloc(sizeof(t_vec3*)
														* slen)))
				return (0);
			if (!((*obj)->poly[i]->e = (t_vec3**)malloc(sizeof(t_vec3*)
														* slen)))
				return (0);
			if (!(split2 = ft_strsplit(split[1], '/')))
				return (0);
			(*obj)->poly[i]->n = (*obj)->n[ft_atoi(split2[1]) - 1];
			j = -1;
			while (++j < slen - 1)
			{
				if (j >= 1)
					if (!(split2 = ft_strsplit(split[j + 1], '/')))
						return (0);
				(*obj)->poly[i]->s[j] = (*obj)->s[ft_atoi(split2[0]) - 1];
				ft_free2d(&split2);
			}
			(*obj)->poly[i]->s[slen - 1] = 0;
			ft_strdel(&line);
			ft_free2d(&split);
			i++;
		}
		if (i == face)
			break ;
	}
	(*obj)->poly[face] = 0;
	return (1);
}

int				fetch_obj(char *path, t_obj **obj)
{
	int		fd;
	int		face;
	int		vertex;
	int		normal;

	face = 0;
	vertex = 0;
	normal = 0;
	if (!check_dir(path))
		return (0);
	if (!(get_obj_data(path, &vertex, &normal, &face)))
		return (0);
	if ((fd = open(path, O_RDONLY)) < 0)
		return (0);
	if (!(get_obj_vertex(fd, vertex, obj)))
		return (0);
	if (!(get_obj_normal(fd, normal, obj)))
		return (0);
	if (!(set_obj_face(fd, face, obj)))
		return (0);
	if (!(prep_poly(obj)))
		return (0);
	return (1);
}
