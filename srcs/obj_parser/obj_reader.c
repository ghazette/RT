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

static int		calc_edge(t_poly *poly)
{
	int i;

	i = 0;
	while (poly->s[i] != 0)
		i++;
	poly->e = malloc(sizeof(t_vec3*) * i);
	i = 0;
	while (poly->s[i] != NULL)
	{
		poly->e[i] = malloc(sizeof(t_vec3));
		vec3_sub(poly->s[i], poly->s[i + 1], poly->e[i]);
		i++;
	}
	vec3_sub(poly->s[i - 1], poly->s[0], poly->e[i]);
	return (1);
}

static int		prep_poly(t_obj *obj)
{
	int i;

	i = 0;
	while (obj->poly[i] != 0)
	{
		calc_edge(obj->poly[i]);
		i++;
	}
	return (1);
}

int				fetch_obj(char *path, t_obj **obj)
{
	int		fd;
	char	*line;
	obj = NULL;

	line = NULL;
	if (!check_dir(path))
		return (0);
	if ((fd = open(path, O_RDONLY)) < 0)
        return (0);
    while (get_next_line(fd, &line))
    {
        printf("%s\n", line);
    }
	prep_poly(obj[0]);
	return (1);
}


