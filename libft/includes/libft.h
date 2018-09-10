/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libft.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:13:23 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/07 12:06:07 by rlossy      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFF_SIZE 4096
# include <string.h>
# include <stdint.h>
# include <wchar.h>
# include "./ft_printf.h"

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

void				ft_bzero(void *s, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				ft_memdel(void **a);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t n);
long long int		ft_atoi(const char *str);
char				*ft_itoa(long long n);
char				*ft_itoa_base(long long nbr, int base);
char				*ft_uitoa_base(unsigned long long nbr, int base);
char				*ft_uitoa(unsigned long long n);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
int					ft_isdigit(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isspace(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_isupper(int c);
int					ft_islower(int c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strncat(char *dest, const char *src, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
size_t				ft_strlen(const char *str);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
void				ft_putchar(char c);
void				ft_putuchar(wchar_t c);
void				ft_putustr(wchar_t *str);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_strdup(const char *s);
int					ft_wordcount(char *str, char c);
char				*ft_strupcase(char *str);
void				ft_swap(int *a, int *b);
void				ft_doubleswap(double *a, double *b);
char				**ft_2d_malloc(int width, int height);
int					ft_heightlen(char **data);
void				ft_str2dcpy(char **dst, char src, size_t n);
void				ft_free2d(char ***str);
void				ft_free3d(char ****str);
void				*ft_realloc(void *ptr, size_t new_size);
int					ft_strlen_ext(char *str, char c);
char				*ft_safecat(char *dest, const char *src);
char				*ft_newcstr(int c, size_t size);
unsigned long		ft_rgbtohex(int r, int g, int b);

/*
** list functions
*/

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *newlist);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

/*
** Wide char functions
*/

size_t				ft_wcslen(const wchar_t *str);
wchar_t				*ft_wstrcpy(wchar_t *dest, const wchar_t *src);
wchar_t				*ft_wstrdup(const wchar_t *src);
wchar_t				*ft_wstrjoin(wchar_t *s1, wchar_t *s2);
wchar_t				*ft_wstrncpy(wchar_t *dest, const wchar_t *src, size_t n);
wchar_t				*ft_wstrndup(const wchar_t *src, size_t n);
wchar_t				*ft_newcwstr(int c, size_t size);

/*
** get next line
*/

typedef struct		s_file
{
	int				fd;
	int				total;
	char			*remain;
}					t_file;

int					get_next_line(const int fd, char **line);
t_list				*check_link_alive(t_list ***addr, t_file ***file,
						const int fd);
t_file				*new_file_or_initlist(const int fd, int mode,
					t_list **filelist, t_file **filein);

#endif
