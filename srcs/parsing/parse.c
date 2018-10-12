/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/06 12:10:55 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 13:38:58 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rt.h"

int		init_vec(t_vec3 *v, char **data)
{
	double	tmp[3];

	if (ft_heightlen(data) != 4)
		return (0);
	tmp[0] = ft_atoi(data[1]) > LIMIT ? LIMIT : ft_atoi(data[1]);
	tmp[0] = ft_atoi(data[1]) < -LIMIT ? -LIMIT : tmp[0];
	tmp[1] = ft_atoi(data[2]) > LIMIT ? LIMIT : ft_atoi(data[2]);
	tmp[1] = ft_atoi(data[2]) < -LIMIT ? -LIMIT : tmp[1];
	tmp[2] = ft_atoi(data[3]) > LIMIT ? LIMIT : ft_atoi(data[3]);
	tmp[2] = ft_atoi(data[3]) < -LIMIT ? -LIMIT : tmp[2];
	v->x = tmp[0];
	v->y = tmp[1];
	v->z = tmp[2];
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
