/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_wstrjoin.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/12 11:30:51 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/31 09:49:39 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

wchar_t		*ft_wstrjoin(wchar_t *s1, wchar_t *s2)
{
	int		len[3];
	int		it[2];
	wchar_t	*str;

	it[0] = 0;
	it[1] = 0;
	if (!s1 || !s2)
		return (NULL);
	len[0] = ft_wcslen(s1);
	len[1] = ft_wcslen(s2);
	len[2] = len[0] + len[1];
	if (!(str = ft_newcwstr('\0', len[2])))
		return (NULL);
	while (it[0] < len[2])
	{
		if (it[0] < len[0])
			str[it[0]] = s1[it[0]];
		else
			str[it[0]] = s2[it[1]++];
		it[0]++;
	}
	str[it[0]] = '\0';
	return (str);
}
