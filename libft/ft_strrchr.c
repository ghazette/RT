/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strrchr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:12:05 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 16:15:48 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *atm;

	atm = (char*)s + ft_strlen(s);
	while (*atm != c)
	{
		if (atm == s)
			return (NULL);
		atm--;
	}
	return (atm);
}
