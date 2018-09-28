#  ************************************************************************** #
#                                                           LE - /            #
#                                                               /             #
#    Makefile                                         .::    .:/ .      .::   #
#                                                  +:+:+   +:    +:  +:+:+    #
#    By: rlossy <rlossy@student.le-101.fr>          +:+   +:    +:    +:+     #
#                                                  #+#   #+    #+    #+#      #
#    Created: 2018/09/07 12:09:52 by rlossy       #+#   ##    ##    #+#       #
#    Updated: 2018/09/07 12:09:52 by rlossy      ###    #+. /#+    ###.fr     #
#                                                          /                  #
#                                                         /                   #
#  ************************************************************************** #

NAME		=	libalgebra.a
HEADER		=   ./includes/
FILENAMES   =   ft_memset.c matrix.c vector.c vector2.c vector3.c vector4.c

SOURCES     =   $(addprefix srcs/, $(FILENAMES))
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
		@echo "\033[33m"
		@mkdir build/

$(NAME): $(OBJECTS)
		@printf "\n\033[1m\033[34m\t\t\t\t⥷ $@⭃\tObject Files\033[0m \
		\033[1m⟿ \t\033[32mCreation Success\033[0m ✅\n"
		@echo "\033[44m\033[37m"
		@sh $(LOADF) $(LOADIR) $@ a n
		@echo "\033[0m"
		@ar crs $@ $(OBJECTS)
		@printf "\n\033[1m\033[34m\t\t\t\t⥷ $@⭃\tProject\t\t\033[0m\033[1m⟿ \
		\033[32mCreation Success\033[0m ✅\n"

build/%.o: srcs/%.c $(HEADER) | build
		@sh $(LOADF) $(LOADIR) $< o y
		@gcc -Wall -Wextra -Werror -I $(HEADER) -c $< -o $@
