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

#include "../../includes/rt.h"

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

static	int		polyloop(t_poly **poly, char ****split,
	t_vec3 ****polydata, int vertex)
{
	int	j;

	j = -1;
	while (++j < (*poly)->ns)
	{
		if (j >= 1)
			if (!((*split)[1] = ft_strsplit((*split)[0][j + 1], '/')))
				return (0);
		(*poly)->s[j] = malloc(sizeof(t_vec3));
		if ((ft_atoi((*split)[1][0])) > vertex ||
			(ft_atoi((*split)[1][0])) <= 0)
			return (0);
		vec3_cpy((*poly)->s[j], (*polydata)[0][ft_atoi((*split)[1][0]) - 1]);
		ft_free2d(&(*split)[1]);
	}
	return (1);
}

int				set_obj_face(int fd, t_obj **obj, t_vec3 ***pdata, int cnt[3])
{
	int		i;
	char	*line;
	char	***split;

	i = 0;
	line = NULL;
	if (!((*obj)->poly = (t_poly**)malloc(sizeof(t_poly*) * (cnt[0]))))
		return (0);
	while ((get_next_line(fd, &line) > 0) || i == cnt[0])
	{
		if (line[0] == 'f' && line[1] == ' ')
		{
			if (!(check(&(*obj)->poly[i], &split, line)))
				return (0);
			if (ft_atoi(split[1][1]) > cnt[2] || ft_atoi(split[1][1]) <= 0)
				return (0);
			vec3_cpy(&(*obj)->poly[i]->n, pdata[1][ft_atoi(split[1][1]) - 1]);
			if (!(polyloop(&(*obj)->poly[i], &split, &pdata, cnt[1])))
				return (0);
			ft_strdel(&line);
			ft_free2d(&split[0]);
			i++;
		}
	}
	return (1);
}

int				fetch_obj(char *path, t_obj **obj)
{
	int		fd;
	int		cnt[3];
	t_vec3	***polydata;

	polydata = malloc(sizeof(t_vec3**) * 2);
	cnt[0] = 0;
	cnt[1] = 0;
	cnt[2] = 0;
	if (!check_dir(path))
		return (0);
	if (!(get_obj_data(path, &cnt[1], &cnt[2], &cnt[0])))
		return (0);
	if ((fd = open(path, O_RDONLY)) < 0)
		return (0);
	if (!(get_obj_vertex(fd, cnt[1], obj, &polydata[0]))
		|| (!(get_obj_normal(fd, cnt[2], obj, &polydata[1])))
		|| (!(set_obj_face(fd, obj, polydata, cnt))))
		return (0);
	(*obj)->npoly = cnt[0];
	if (!(prep_poly(obj)))
		return (0);
	(*obj)->form = OBJ_FROMFILE;
	return (1);
}
