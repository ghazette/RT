/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstmap.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:06:54 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 16:16:16 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdlib.h>

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *newlist;
	t_list *tmp;
	t_list *ptr;

	if (lst && f)
	{
		tmp = f(lst);
		if ((newlist = ft_lstnew(tmp->content, tmp->content_size)) == NULL)
			return (NULL);
		ptr = newlist;
		lst = lst->next;
		while (lst)
		{
			tmp = f(lst);
			if ((newlist->next = ft_lstnew(tmp->content,
							tmp->content_size)) == NULL)
				return (NULL);
			newlist = newlist->next;
			lst = lst->next;
		}
		return (ptr);
	}
	return (NULL);
}
