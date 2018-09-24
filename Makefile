#  ************************************************************************** #
#                                                           LE - /            #
#                                                               /             #
#    Makefile                                         .::    .:/ .      .::   #
#                                                  +:+:+   +:    +:  +:+:+    #
#    By: rlossy <rlossy@student.le-101.fr>          +:+   +:    +:    +:+     #
#                                                  #+#   #+    #+    #+#      #
#    Created: 2018/09/06 16:13:08 by rlossy       #+#   ##    ##    #+#       #
#    Updated: 2018/09/06 16:13:08 by rlossy      ###    #+. /#+    ###.fr     #
#                                                          /                  #
#                                                         /                   #
#  ************************************************************************** #

NAME		=	RT
HEADER		=	./includes/

LIB_DIR		=	./libft
LIBX_DIR	=	./minilibx_macos
LIBAL_DIR   =   ./libalgebra
LIBMP_DIR   =   ./libbmp

FILENAMES	=	main/main.c main/mlx.c main/ray.c main/rotate.c main/utils.c main/utils2.c
FILENAMES   +=  main/utils1.c main/camera.c main/light.c main/phong.c
FILENAMES   +=  input/click.c input/key.c input/key_input.c input/key_rot.c
FILENAMES   +=  input/mouse_input.c interface/interface.c interface/interface1.c
FILENAMES   +=  objects/cone.c objects/cylinder.c objects/plane.c objects/composed.c
FILENAMES   +=  objects/sphere.c parsing/fetch.c parsing/fetch2.c
FILENAMES   +=  parsing/file_reader.c parsing/parse.c

OBJECTS		=	$(addprefix build/, $(FILENAMES:.c=.o))

L_FT		=	$(LIB_DIR)
LIB_LNK		=	-L $(L_FT) -l ft
LIB_INC		=	-I $(L_FT)/libft.h

LX_FT		=	$(LIBX_DIR)
LIBX_LNK	=	-L $(LX_FT) -l mlx
LIBX_INC	=	-I $(LX_FT)/mlx.h

LBAL_FT     =   $(LIBAL_DIR)
LIBAL_LNK   =   -L $(LBAL_FT) -l algebra
LIBAL_INC   =   -I $(LBAL_FT)/libalgebra.h

LBMP_FT     =	$(LIBMP_DIR)
LIBMP_LNK	=	-L $(LBMP_FT) -l bmp
LIBMP_INC	=	-I $(LBMP_FT)/libbmp.h $(LBMP_FT)/bmp.h

FLAGS		=	-Wall -Wextra -Werror -O2 -g
FLAGX		=	-framework OpenGL -framework AppKit

LOADIR		=	./extra/Progress_Bar-for-Makefile
LOADF		=	$(LOADIR)/loading.sh

.PHONY: all clean fclean re


all: $(NAME)

clean:
	@echo "\033[31m"
	@sh $(LOADF) $(LOADIR) $@ r n $(NAME)
	@rm -rf build/
	@printf "\n\033[1m\033[34m\t\t\t\t⥷ $(NAME)⭃\t\tObject Files\t\033[0m\
	\033[1m⟿ \t\033[31mDeletion Success\033[0m ✅\n"

cleanlib:
	@$(MAKE) -C $(L_FT) clean
	@$(MAKE) -C $(LX_FT) clean
	@$(MAKE) -C $(LBAL_FT) clean
	@$(MAKE) -C $(LBMP_FT) clean

fclean: clean
	@echo "\033[31m"
	@sh $(LOADF) $(LOADIR) $@ r n $(NAME)
	@rm -f $(NAME)
	@printf "\n\033[1m\033[34m\t\t\t\t⥷ $(NAME)⭃\t\tCompiled Files\t\033[0m\
	\033[1m⟿ \t\033[31mDeletion Success\033[0m ✅\n"
	@$(MAKE) -C $(L_FT) fclean
	@$(MAKE) -C $(LX_FT) fclean
	@$(MAKE) -C $(LBAL_FT) fclean
	@$(MAKE) -C $(LBMP_FT) fclean

re: 
	@$(MAKE) fclean 
	@$(MAKE) all

build: 
	@echo "\033[35m"
	@mkdir build/
	@mkdir build/main
	@mkdir build/input
	@mkdir build/interface
	@mkdir build/objects
	@mkdir build/parsing

$(NAME): $(OBJECTS)
	@printf "\n\033[1m\033[34m\t\t\t\t⥷ $@⭃\t\tObject Files\033[0m \
		\033[1m⟿ \t\033[32mCreation Success\033[0m ✅\n"
	@$(MAKE) -C $(L_FT)
	@$(MAKE) -C $(LBMP_FT)
	@$(MAKE) -C $(LBAL_FT)
	@$(MAKE) -C $(LX_FT)
	@echo "\033[42m\033[30m"
	@sh $(LOADF) $(LOADIR) $@ e n $(NAME)
	@echo "\033[0m"
	@gcc -I $(HEADER) $(OBJECTS) $(LIB_LNK) $(LIBX_LNK) $(LIBAL_LNK) \
	$(LIBMP_LNK) $(FLAGX) -o $@
	@printf "\n\033[1m\033[34m\t\t\t\t⥷ $@⭃\t\tProject\t\t\033[0m \033[1m⟿  \
		\033[32mCreation Success\033[0m ✅\n"

build/%.o: srcs/%.c $(HEADER) | build
	@sh $(LOADF) $(LOADIR) $< o y
	@gcc $(LIB_INC) -I $(HEADER) -c $< -o $@
