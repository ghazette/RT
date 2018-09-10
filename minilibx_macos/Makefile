# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: rlossy <marvin@le-101.fr>                  +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/04/17 14:32:14 by rlossy       #+#   ##    ##    #+#        #
#   Updated: 2018/05/02 14:34:46 by rlossy      ###    #+. /#+    ###.fr     # #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME		=	libmlx.a
HEADER		=	mlx.h
FILENAMES	=	mlx_shaders.c mlx_xpm.c mlx_int_str_to_wordtab.c
SRCS		=	mlx_new_window.m mlx_init_loop.m mlx_new_image.m

SOURCES		=   $(addprefix ./, $(FILENAMES))
OBJ			=   $(addprefix build/, $(SRCS:.m=.o))
OBJECTS		=   $(addprefix build/, $(FILENAMES:.c=.o))

FLAGS		=	-O2

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
		@rm -f mlx_app
		@printf "\n\033[1m\033[34m\t\t\t\t⥷ $(NAME)⭃\tCompiled Files\033[0m \
		\033[1m⟿ \t\033[31mDeletion Success\033[0m ✅\n"

re: 
	@$(MAKE) fclean
	@$(MAKE) all

build:
		@echo "\033[1m"
		@mkdir build/

$(NAME): $(OBJECTS) $(OBJ)
		@echo "\033[0m"
		@printf "\n\033[1m\033[34m\t\t\t\t⥷ $(NAME)⭃\tObject Files\033[0m \
		\033[1m⟿ \t\033[32mCreation Success\033[0m ✅\n"
		@echo "\033[7m"
		@sh $(LOADF) $(LOADIR) $@ a n
		@echo "\033[0m"
		@ar crs $@ $(OBJECTS) $(OBJ)
		@printf "\n\033[1m\033[34m\t\t\t\t⥷ $@⭃ \tProject\t\t\033[0m\033[1m⟿ \
		\033[32mCreation Success\033[0m ✅\n"

build/%.o: ./%.c $(HEADER) | build
		@sh $(LOADF) $(LOADIR) $< o y
		@gcc $(FLAGS) -c $< -o $@

build/%.o: ./%.m $(HEADER) | build
		@sh $(LOADF) $(LOADIR) $< o y
		@gcc $(FLAGS) -c $< -o $@
