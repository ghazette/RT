/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils1.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/23 23:35:52 by mkulhand     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/06 17:45:18 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	print_poly(t_poly *poly)
{
	int	nbv;
	int i;

	i = 0;
	printf("%d\n", poly->nvertex);
	printf("vertex:\n");
	while (i < poly->nvertex)
	{
		// printf("%s\n", parse_vec(*startPtr));
		// printf("%f\n", poly->s[0]->x);
		printf("%s\n",parse_vec(*poly->s[i]));
		i++;
	}
	i = 0;
	printf("edges:\n");
	while (i < poly->nvertex)
	{
		printf("%s\n",parse_vec(*poly->e[i]));
		i++;
	}
}