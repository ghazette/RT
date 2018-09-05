/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstadd.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:06:31 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 16:12:33 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_lstadd(t_list **alst, t_list *newlist)
{
	t_list	*alstcpy;

	alstcpy = (*alst);
	if (newlist != NULL)
	{
		(*alst) = newlist;
		(*alst)->next = alstcpy;
	}
}
