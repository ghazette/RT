/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   obj_reader.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mkulhand <mkulhand@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/07 13:03:47 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/07 13:03:49 by mkulhand    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

static int		get_obj_data(char *path, int *vertex, int *normal, int *face)
{
	char	*line;
	int		fd;

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

int			get_obj_vertex(int fd, int vertex, t_obj **obj)
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
			vector3d((*obj)->s[i], ft_atoi(split[1]), ft_atoi(split[2]), ft_atoi(split[3]));
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

int			get_obj_normal(int fd, int normal, t_obj **obj)
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
			vector3d((*obj)->n[i], ft_atoi(split[1]), ft_atoi(split[2]), ft_atoi(split[3]));
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

int			set_obj_face(int fd, int face, t_obj **obj)
{
	int		i;
	char	*line;
	char	**splitvn;
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
			if (!((*obj)->poly[0] = malloc(sizeof(t_poly))))
				return (0);
			if (!((*obj)->poly[0]->s = (t_vec3**)malloc(sizeof(t_vec3*) * ft_heightlen(split))))
				return (0);
			if (!(splitvn = ft_strsplit(split[1], '/')))
				return (0);
			(*obj)->poly[0]->n = (*obj)->n[ft_atoi(splitvn[1])];
			printf("%f\n", (*obj)->poly[0]->n->x);
			exit(0);
			//vector3d((*obj)->n[i], ft_atoi(split[1]), ft_atoi(split[2]), ft_atoi(split[3]));
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
	int i = 0;
	while ((*obj)->s[i] != 0)
	{
		printf("vertex : %f %f %f\n", (*obj)->s[i]->x, (*obj)->s[i]->y, (*obj)->s[i]->z);
		i++;
	}
	if (!(get_obj_normal(fd, normal, obj)))
		return (0);
	i = 0;
	while ((*obj)->n[i] != 0)
	{
		printf("normal %d : %f %f %f\n", i,(*obj)->n[i]->x, (*obj)->n[i]->y, (*obj)->n[i]->z);
		i++;
	}
	if (!(set_obj_face(fd, face, obj)))
		return (0);
	printf("vertex : %d\nfaces : %d\nnormal : %d\n", vertex, face, normal);
	return (1);
}


