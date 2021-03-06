/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_bzero.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:05:15 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 16:11:29 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"
#include <string.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned char *ss;

	ss = s;
	while (n--)
		*ss++ = '\0';
}
