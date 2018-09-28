#  ************************************************************************** #
#                                                           LE - /            #
#                                                               /             #
#    Makefile                                         .::    .:/ .      .::   #
#                                                  +:+:+   +:    +:  +:+:+    #
#    By: rlossy <rlossy@student.le-101.fr>          +:+   +:    +:    +:+     #
#                                                  #+#   #+    #+    #+#      #
#    Created: 2018/09/06 16:28:57 by rlossy       #+#   ##    ##    #+#       #
#    Updated: 2018/09/06 17:07:35 by rlossy      ###    #+. /#+    ###.fr      #
#                                                          /                  #
#                                                         /                   #
#  ************************************************************************** #

NAME		=	libft.a
HEADER		=   ./includes/
FILENAMES   =   ft_atoi.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c
FILENAMES   +=  ft_isprint.c ft_isspace.c ft_tolower.c ft_toupper.c ft_strcat.c
FILENAMES   +=  ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strcmp.c
FILENAMES   +=  ft_strncmp.c ft_strcpy.c ft_strncpy.c ft_strdup.c ft_strnstr.c
FILENAMES   +=  ft_strstr.c ft_strlen.c ft_memalloc.c ft_memdel.c ft_strnew.c
FILENAMES   +=  ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c
FILENAMES   +=  ft_strmapi.c ft_strequ.c ft_strnequ.c ft_putuchar.c ft_putchar.c
FILENAMES   +=  ft_putchar_fd.c ft_putustr.c ft_putstr.c ft_putstr_fd.c
FILENAMES   +=  ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_itoa.c
FILENAMES   +=  ft_bzero.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c
FILENAMES   +=  ft_memdel.c ft_memmove.c ft_memset.c ft_strsub.c ft_strjoin.c
FILENAMES   +=  ft_strtrim.c ft_strsplit.c ft_wordcount.c ft_lstnew.c
FILENAMES   +=  ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c
FILENAMES   +=  ft_itoa_base.c ft_strupcase.c ft_isupper.c ft_islower.c
FILENAMES   +=  ft_swap.c ft_2d_malloc.c ft_heightlen.c ft_str2dcpy.c
FILENAMES   +=  ft_free2d.c ft_free3d.c ft_realloc.c ft_strlen_ext.c
FILENAMES   +=  ft_safecat.c ft_wcslen.c ft_wstrcpy.c ft_wstrdup.c ft_wstrjoin.c
FILENAMES   +=  ft_wstrncpy.c ft_wstrndup.c ft_newcstr.c ft_newcwstr.c
FILENAMES   +=  ft_putuchar.c ft_putustr.c ft_uitoa.c ft_uitoa_base.c
FILENAMES   +=  get_next_line.c conv_and_parse.c conv_and_parse2.c
FILENAMES   +=  display.c ft_printf.c getters.c getters2.c parse_cs.c
FILENAMES   +=  parse_cs_utf.c parse_di.c parse_xoup.c prtfdata.c utils.c
FILENAMES   +=  ft_rgbtohex.c ft_doubleswap.c ft_atof.c ft_splitwhitespace.c

SOURCES     =   $(addprefix ./, $(FILENAMES))
OBJECTS     =   $(addprefix build/, $(FILENAMES:.c=.o))

LOADIR		=	../extra/Progress_Bar-for-Makefile
LOADF		=	$(LOADIR)/loading.sh

.PHONY: all clean fclean re


all: $(NAME)


clean:
		@echo "\033[31m"
		@sh $(LOADF) $(LOADIR) $@ r n $(NAME)
		@rm -rf build/
		@printf "\n\033[1m\033[34m\t\t\t\t⥷ $(NAME)⭃\tObject Files\033[0m \
		\033[1m⟿ \t\033[31mDeletion Success\033[0m ✅\n"

fclean: clean
		@echo "\033[31m"
		@sh $(LOADF) $(LOADIR) $@ r n $(NAME)
		@rm -f $(NAME)
		@printf "\n\033[1m\033[34m\t\t\t\t⥷ $(NAME)⭃\tCompiled Files\033[0m \
		\033[1m⟿ \t\033[31mDeletion Success\033[0m ✅\n"

re:
		@$(MAKE) fclean
		@$(MAKE) all

build:
		@echo "\033[36m"
		@mkdir build/
		@mkdir build/ft_printf

$(NAME): $(OBJECTS)
		@printf "\n\033[1m\033[34m\t\t\t\t⥷ $(NAME)⭃\tObject Files\033[0m \
		\033[1m⟿ \t\033[32mCreation Success\033[0m ✅\n"
		@echo "\033[43m\033[30m"
		@sh $(LOADF) $(LOADIR) $@ a n
		@echo "\033[0m"
		@ar crs $@ $(OBJECTS)
		@printf "\n\033[1m\033[34m\t\t\t\t⥷ $@⭃ \tProject\t\t\033[0m\033[1m⟿ \
		\033[32mCreation Success\033[0m ✅\n"

build/%.o: ./%.c $(HEADER) | build
		@sh $(LOADF) $(LOADIR) $< o y
		@gcc -Wall -Wextra -Werror -I $(HEADER) -c $< -o $@
