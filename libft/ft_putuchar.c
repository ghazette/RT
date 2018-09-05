/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putuchar.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/26 10:51:55 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/31 10:38:44 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"
#include <unistd.h>

static void		bigunicode(wchar_t c)
{
	unsigned char	bytes[4];

	bytes[0] = (c >> 18) + 240;
	if (c >= 65536 && c <= 262143)
		bytes[1] = ((c >> 12) ^ ((c >> 18) << 12)) + 128;
	if (c >= 262144 && c <= 524287)
		bytes[1] = ((c >> 12) ^ ((c >> 18) << 12)) + 64;
	if (c >= 524288 && c <= 1048575)
		bytes[1] = ((c >> 12) ^ ((c >> 18) << 12)) + 0;
	if (c >= 1048576)
		bytes[1] = ((c >> 12) ^ ((c >> 18) << 12)) + 128;
	bytes[2] = ((c >> 6) ^ ((c >> 12) << 6)) + 128;
	bytes[3] = (c ^ ((c >> 6) << 6)) + 128;
	write(1, bytes, 4);
}

void			ft_putuchar(wchar_t c)
{
	unsigned char bytes[3];

	if (c >= 128 && c <= 2047)
	{
		bytes[0] = (c >> 6) + 192;
		bytes[1] = (c ^ ((c >> 6) << 6)) + 128;
		write(1, bytes, 2);
	}
	else if (c >= 2048 && c <= 65535)
	{
		bytes[0] = (c >> 12) + 224;
		bytes[1] = ((c >> 6) ^ ((c >> 12) << 6)) + 128;
		bytes[2] = (c ^ ((c >> 6) << 6)) + 128;
		write(1, bytes, 3);
	}
	else if (c >= 65536 && c <= 1114111)
		bigunicode(c);
}
