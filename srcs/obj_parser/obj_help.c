/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   obj_help.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlossy <rlossy@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/01 13:32:25 by rlossy       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/01 13:32:25 by rlossy      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rt.h"

int				get_obj_vertex(int fd, int vertex, t_obj **obj, t_vec3 ***s)
{
	int		i;
	char	*line;
	char	**split;

	i = 0;
	line = NULL;
	if (!((*s) = (t_vec3**)malloc(sizeof(t_vec3*) * vertex)))
		return (0);
	while ((get_next_line(fd, &line) > 0) || i == vertex)
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
	while ((get_next_line(fd, &line) > 0) || i == normal)
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
