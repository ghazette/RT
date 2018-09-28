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

static int		prep_poly(t_obj **obj)
{
	int i;

	i = 0;
	while (i < (*obj)->npoly)
	{
		calc_edge((*obj)->poly[i], 1);
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
	if (*face == 0 || *vertex == 0)
		return (0);
	close(fd);
	return (1);
}

int				get_obj_vertex(int fd, int vertex, t_obj **obj, t_vec3 ***s)
{
	int		i;
	char	*line;
	char	**split;

	i = 0;
	line = NULL;
	if (!((*s) = (t_vec3**)malloc(sizeof(t_vec3*) * vertex)))
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 'v' && line[1] == ' ')
		{
			if (!(split = ft_strsplit(line, ' ')) ||
				!((*s)[i] = malloc(sizeof(t_vec3))))
				return (0);
			if (ft_heightlen(split) < 4)
				return (0);
			vector3d((*s)[i], atof(split[1]) + (*obj)->pos.x,
				atof(split[2]) + (*obj)->pos.y, atof(split[3]) + (*obj)->pos.z);
			ft_strdel(&line);
			ft_free2d(&split);
			i++;
		}
		if (i == vertex)
			break ;
	}
	return (1);
}

int				get_obj_normal(int fd, int normal, t_obj **obj, t_vec3 ***n)
{
	int		i;
	char	*line;
	char	**split;

	i = 0;
	line = NULL;
	if (!(*n = (t_vec3**)malloc(sizeof(t_vec3*) * normal)))
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 'v' && line[1] == 'n')
		{
			if (!(split = ft_strsplit(line, ' ')) ||
				!((*n)[i] = malloc(sizeof(t_vec3))))
				return (0);
			if (ft_heightlen(split) < 4)
				return (0);
			vector3d((*n)[i], atof(split[1]), atof(split[2]),
					atof(split[3]));
			ft_strdel(&line);
			ft_free2d(&split);
			i++;
		}
		if (i == normal)
			break ;
	}
	return (1);
}

static int		check(t_poly **poly, char ****split, char *line)
{
	if (!((*split) = malloc(sizeof(char**) * 2)))
		return (0);
	if (!((*split)[0] = ft_strsplit(line, ' '))
		|| !((*poly) = malloc(sizeof(t_poly))))
		return (0);
	(*poly)->ns = ft_heightlen((*split)[0]) - 1;
	if (!((*poly)->s = (t_vec3**)malloc(sizeof(t_vec3*)
										* (*poly)->ns)))
		return (0);
	if (!((*split)[1] = ft_strsplit((*split)[0][1], '/')))
		return (0);
	return (1);
}

static	int		polyloop(t_poly **poly, char ****split, t_vec3 ****polydata, int vertex)
{
	int	j;

	j = -1;
	while (++j < (*poly)->ns)
	{
		if (j >= 1)
			if (!((*split)[1] = ft_strsplit((*split)[0][j + 1], '/')))
				return (0);
		(*poly)->s[j] = malloc(sizeof(t_vec3));
		if ((ft_atoi((*split)[1][0])) > vertex || (ft_atoi((*split)[1][0])) <= 0)
			return (0);
		vec3_cpy((*poly)->s[j], (*polydata)[0][ft_atoi((*split)[1][0]) - 1]);
		ft_free2d(&(*split)[1]);
	}
	return (1);
}

int				set_obj_face(int fd, int face, t_obj **obj, t_vec3 ***pdata, int vertex, int normal)
{
	int		i;
	int		i_spl;
	char	*line;
	char	***split;

	i = 0;
	line = NULL;
	if (!((*obj)->poly = (t_poly**)malloc(sizeof(t_poly*) * (face))))
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 'f' && line[1] == ' ')
		{
			if (!(check(&(*obj)->poly[i], &split, line)))
				return (0);
			// if (ft_heightlen(split) )
			if (ft_atoi(split[1][1]) > normal || ft_atoi(split[1][1]) <= 0)
				return (0);
			vec3_cpy(&(*obj)->poly[i]->n, pdata[1][ft_atoi(split[1][1]) - 1]);
			if (!(polyloop(&(*obj)->poly[i], &split, &pdata, vertex)))
				return (0);
			ft_strdel(&line);
			ft_free2d(&split[0]);
			i++;
		}
		if (i == face)
			break ;
	}
	return (1);
}

int				fetch_obj(char *path, t_obj **obj)
{
	int		fd;
	int		face;
	int		vertex;
	int		normal;
	t_vec3	***polydata;

	polydata = malloc(sizeof(t_vec3**) * 2);
	face = 0;
	vertex = 0;
	normal = 0;
	if (!check_dir(path))
		return (0);
	if (!(get_obj_data(path, &vertex, &normal, &face)))
		return (0);
	if ((fd = open(path, O_RDONLY)) < 0)
		return (0);
	if (!(get_obj_vertex(fd, vertex, obj, &polydata[0]))
		|| (!(get_obj_normal(fd, normal, obj, &polydata[1])))
		|| (!(set_obj_face(fd, face, obj, polydata, vertex, normal))))
		return (0);
	(*obj)->npoly = face;
	if (!(prep_poly(obj)))
		return (0);
	(*obj)->form = OBJ_FROMFILE;
	return (1);
}
