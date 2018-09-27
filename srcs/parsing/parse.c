/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/06 12:10:55 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/27 10:33:29 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

int		init_vec(t_vec3 *v, char **data)
{
	if (ft_heightlen(data) != 4)
		return (0);
	v->x = ft_atoi(data[1]);
	v->y = ft_atoi(data[2]);
	v->z = ft_atoi(data[3]);
	return (1);
}

int		check_file(char *fn)
{
	char	*line;
	int		chk;
	int		fd;

	if (!(fd = open(fn, O_RDONLY)))
		return (0);
	chk = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (!ft_strcmp(line, ""))
			chk++;
		else
			chk = 0;
		if (chk > 1)
			return (0);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	close(fd);
	return (1);
}

int		get_nb_obj(char *fn, int ret[2])
{
	int		fd;
	char	*line;

	ret[0] = 0;
	ret[1] = 0;
	fd = open(fn, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		if (!ft_strcmp(line, "OBJECT"))
			ret[0]++;
		if (!ft_strcmp(line, "SPOT"))
			ret[1]++;
		ft_strdel(&line);
	}
	close(fd);
	if (ret[0] == 0)
		return (0);
	return (1);
}
