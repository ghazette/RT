/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/20 17:29:19 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/11 10:08:48 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rt.h"

char		*get_type(int type)
{
	if (type == SPHERE)
		return ("SPHERE");
	if (type == PLANE)
		return ("PLANE");
	if (type == CYLINDER)
		return ("CYLINDER");
	if (type == CONE)
		return ("CONE");
	if (type == COMPOSED)
		return ("COMPOSED");
	return (NULL);
}

char		*parse_vec(t_vec3 v)
{
	char	*str;
	char	*nb;

	if (!(str = malloc(sizeof(char) * 20)))
		return (NULL);
	if (!(nb = ft_itoa(v.x)))
		return (NULL);
	str = ft_strcpy(str, nb);
	str = ft_strcat(str, " ");
	ft_strdel(&nb);
	if (!(nb = ft_itoa(v.y)))
		return (NULL);
	str = ft_strcat(str, nb);
	str = ft_strcat(str, " ");
	ft_strdel(&nb);
	if (!(nb = ft_itoa(v.z)))
		return (NULL);
	str = ft_strcat(str, nb);
	ft_strdel(&nb);
	return (str);
}

void		usage(void)
{
	ft_printf("usage: ./RT <FILE_PATH>\n");
}

int			check_dir(char *fn)
{
	int		fd;
	char	buf[2];

	fd = open(fn, O_RDONLY);
	if (read(fd, buf, 2) == -1)
		return (0);
	close(fd);
	return (1);
}

char		*rand_string(int len)
{
	char	*ret;
	int		i;

	ret = malloc(len + 1);
	i = 0;
	while (i < len)
		ret[i++] = rand() % (91 - 65) + 65;
	ret[i] = '\0';
	return (ret);
}
