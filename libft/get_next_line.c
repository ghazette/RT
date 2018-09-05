/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/19 10:51:08 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/07 17:23:44 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"
#include <unistd.h>
#include <stdlib.h>

t_file			*new_file_or_initlist(const int fd, int mode, t_list **filelist,
	t_file **filein)
{
	t_file *file;

	if (mode == 0)
	{
		if (!(file = (t_file*)malloc(sizeof(t_file))))
			return (NULL);
		file->fd = fd;
		file->total = 0;
		file->remain = NULL;
		return (file);
	}
	if (fd < 0)
		return (NULL);
	if (!(*filelist))
	{
		if (!(*filelist = check_link_alive(&filelist, &filein, fd)))
			return (NULL);
	}
	else if (!(check_link_alive(&filelist, &filein, fd)))
		return (NULL);
	return (*filein);
}

t_list			*check_link_alive(t_list ***addr, t_file ***file, const int fd)
{
	t_list *tmp;
	t_file *newfile;
	t_list *new;

	tmp = **addr;
	while (tmp)
	{
		if ((((t_file *)tmp->content)->fd) == fd)
			if ((**file = ((t_file *)tmp->content)))
				return (tmp);
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	if (!(newfile = new_file_or_initlist(fd, 0, NULL, NULL)))
		return (NULL);
	if (!(new = ft_lstnew(newfile, sizeof(t_file))))
		return (NULL);
	free(newfile);
	**file = ((t_file *)new->content);
	if (!tmp)
		tmp = new;
	else
		tmp->next = new;
	return (tmp);
}

static int		del_file(t_list **filelist, t_file **file, t_list *before)
{
	t_list *tmp;
	t_list *next;

	tmp = *filelist;
	if ((*file)->total <= 0)
		while (tmp)
		{
			if ((((t_file *)tmp->content)->fd) == (*file)->fd)
			{
				next = tmp->next;
				if ((*file)->remain)
					free((*file)->remain);
				free(*file);
				free(tmp);
				if (before)
					before->next = next;
				else
					*filelist = next;
				return (1);
			}
			before = tmp;
			tmp = tmp->next;
		}
	return (0);
}

static int		core_func(char ***line, t_file **file)
{
	int		len;
	char	*tmp;

	len = ft_strlen_ext((*file)->remain, '\n');
	if (!(**line = ft_strnew(len)))
		return (-1);
	**line = ft_strncat(**line, (*file)->remain, len);
	if (!(tmp = ft_strsub((*file)->remain, len + 1, (*file)->total)))
		return (-1);
	ft_strdel(&((*file)->remain));
	(*file)->total -= len + 1;
	if (!((*file)->remain = ft_strdup(tmp)))
		return (-1);
	ft_strdel(&tmp);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	int				ret;
	static t_list	*filelist;
	t_list			*before;
	t_file			*file;

	before = NULL;
	if (!(new_file_or_initlist(fd, 1, &filelist, &file)))
		return (-1);
	while ((ret = read(file->fd, &buf, BUFF_SIZE)))
	{
		if (ret < 0)
			return (-1);
		buf[ret] = '\0';
		file->total += ret;
		if (!(file->remain = (!(file->remain)) ? ft_strdup(buf)
		: ft_safecat(file->remain, buf)))
			return (-1);
		if (ft_strchr(file->remain, '\n') != NULL)
			return (core_func(&line, &file));
	}
	if (del_file(&filelist, &file, before))
		return (0);
	return (core_func(&line, &file));
}
