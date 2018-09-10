/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prtfdata.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/27 13:41:43 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/24 10:26:53 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** create a new t_prtfdata structure and return it
*/

t_prtfdata			*create_elem(void)
{
	t_prtfdata *elem;

	if (!(elem = (t_prtfdata*)malloc(sizeof(t_prtfdata))))
		return (NULL);
	elem->i = 0;
	elem->size = 0;
	elem->wlen = 0;
	elem->len = 0;
	elem->zeropad = 0;
	elem->pluspad = 0;
	elem->rspace = 0;
	elem->lspace = 0;
	elem->flag = 0;
	elem->havespace = 0;
	elem->format = 0;
	elem->htag = 0;
	elem->precision = 0;
	elem->type = TYPE_CHAR;
	elem->str.wch = NULL;
	elem->str.ch = NULL;
	return (elem);
}

/*
** delete a structure
*/

void				pops(t_prtfdata **lst)
{
	if (*lst)
	{
		if ((*lst)->type == TYPE_CHAR && (*lst)->str.ch != NULL)
			ft_strdel(&((*lst)->str.ch));
		if ((*lst)->type == TYPE_WCHAR && (*lst)->str.wch != NULL)
			free((*lst)->str.wch);
		free(*lst);
		*lst = NULL;
	}
}

/*
** reset t_prtfdata structure
** update i & size variables
*/

void				update(t_prtfdata **lst, long long int len)
{
	if ((*lst)->str.ch != NULL && (*lst)->type == TYPE_CHAR)
		ft_strdel(&((*lst)->str.ch));
	if ((*lst)->str.wch != NULL && (*lst)->type == TYPE_WCHAR)
		free((*lst)->str.wch);
	(*lst)->str.wch = NULL;
	(*lst)->i += len;
	(*lst)->size += (*lst)->len;
	(*lst)->len = 0;
	(*lst)->wlen = 0;
	(*lst)->zeropad = 0;
	(*lst)->pluspad = 0;
	(*lst)->rspace = 0;
	(*lst)->lspace = 0;
	(*lst)->flag = 0;
	(*lst)->havespace = 0;
	(*lst)->format = 0;
	(*lst)->htag = 0;
	(*lst)->precision = 0;
	(*lst)->type = TYPE_CHAR;
}
