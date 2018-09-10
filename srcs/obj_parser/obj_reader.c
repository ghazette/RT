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

int				fetch_obj(char *path, t_obj **obj)
{
    printf("obj path detected\n%s\n", path);
	int		fd;
	char	*line;

	line = NULL;
	if (!check_dir(path) && (line = NULL) == NULL)
		return (0);
	if ((fd = open(path, O_RDONLY)) < 0)
        return (0);
    while (get_next_line(fd, &line))
    {
        printf("%s\n", line);
    }
	return (1);
}


