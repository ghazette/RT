/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/26 15:43:26 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/31 11:55:36 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "../../includes/libft.h"
# include <wchar.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# define FLAGS_H 0x10
# define FLAGS_HH 0x20
# define FLAGS_LL 0x30
# define FLAGS_L 0x40
# define FLAGS_J 0x50
# define FLAGS_Z 0x60
# define TYPE_CHAR 0x70
# define TYPE_WCHAR 0x80
# define RSPACE 0x90
# define LSPACE 0x100

typedef union			u_char
{
	char				*ch;
	wchar_t				*wch;
}						t_char;

typedef struct			s_prtfdata
{
	long long int		len;
	long long int		wlen;
	long long int		i;
	long long int		size;
	long long int		rspace;
	long long int		lspace;
	int					zeropad;
	int					pluspad;
	int					havespace;
	int					htag;
	int					flag;
	int					format;
	long long int		precision;
	union u_char		str;
	int					type;
}						t_prtfdata;

int						ft_printf(const char *format, ...);
t_prtfdata				*create_elem(void);
void					pops(t_prtfdata **lst);
void					update(t_prtfdata **lst, long long int len);

void					display(t_prtfdata **elm);
void					buffer_display(char **buffer, const char *format,
						long long int i, int action);

int						get_flag(const char *str, size_t len,
							t_prtfdata **elem);
int						get_htag(const char *str, size_t len,
							t_prtfdata **elem);
int						get_precision(const char *str, size_t len,
							va_list args);
int						get_pluspad(const char *str, size_t len,
							t_prtfdata **elem);
void					get_rspaced(t_prtfdata **elm, const char *str,
							size_t len);

size_t					format_parse(t_prtfdata **elm, const char *str,
							va_list args);
int						conv_and_parse(t_prtfdata **elm, va_list args);
int						parse(t_prtfdata **elm);
int						conv_notype(t_prtfdata **elm);
int						conv(t_prtfdata **elm, intmax_t n, uintmax_t nu);
int						conv_int(t_prtfdata **elm, va_list args);
int						conv_char(t_prtfdata **elm, va_list args);
int						conv_uint(t_prtfdata **elm, va_list args);
int						conv_lint(t_prtfdata **elm, va_list args);
int						conv_ptr(t_prtfdata **elm, va_list args);
int						parse_di(t_prtfdata **elm);
int						parse_xoup(t_prtfdata **elm);
int						parse_c(t_prtfdata **elm);
int						parse_s(t_prtfdata **elm);
int						parse_notype(t_prtfdata **elm);
int						parse_c_utf(t_prtfdata **elm);
int						parse_s_utf(t_prtfdata **elm);
int						purge(const char *str, size_t *len2, va_list args);
char					*char_concat(char **str, int c, size_t n, int lrspace);
wchar_t					*wchar_concat(wchar_t **str, int c, size_t n,
							int lrspace);
size_t					ft_getbytesize(wchar_t *data);
size_t					ft_getcbytesize(wchar_t c);

#endif
