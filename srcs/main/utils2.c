/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils2.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/23 23:35:52 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/11 13:19:48 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

void	free_poly(t_obj *obj)
{
	int i;
	int j;

	i = 0;
	if (obj->npoly > 0)
	{
		while (i < obj->npoly)
		{
			j = 0;
			while (j < obj->poly[i]->ns)
			{
				free(obj->poly[i]->s[j]);
				free(obj->poly[i]->e[j]);
				j++;;
			}	
			free(obj->poly[i]->s);
			free(obj->poly[i]->e);
			free(obj->poly[i]);
			obj->poly[i] = NULL;
			i++;
		}
		free(obj->poly);
	}
}
