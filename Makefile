# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2017/11/28 11:28:16 by gzanarel     #+#   ##    ##    #+#        #
#    Updated: 2018/06/11 17:55:21 by ghazette    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = rtv1

OS = $(shell uname)

SRC_PATH = ./srcs/

SRC_ROOT = $(addprefix $(SRC_PATH), camera.c light.c main.c mlx.c phong.c ray.c rotate.c utils.c utils1.c)

OBJ_PATH = ./srcs/objects/

SRC_OBJ = $(addprefix $(OBJ_PATH), cone.c cylinder.c plane.c sphere.c composed.c)

INTER_PATH = ./srcs/interface/

SRC_INTER = $(addprefix $(INTER_PATH), interface.c interface1.c)

PARSE_PATH = ./srcs/parsing/

SRC_PARSE = $(addprefix $(PARSE_PATH), fetch.c fetch2.c file_reader.c parse.c)

INPUT_PATH = ./srcs/input/

SRC_INPUT = $(addprefix $(INPUT_PATH), click.c key.c key_input.c key_rot.c mouse_input.c)

OBJ_PARSER_PATH = ./srcs/obj_parser/

SRC_OBJ_PARSER = $(addprefix $(OBJ_PARSER_PATH), obj_reader.c)

SRC += $(SRC_ROOT)

SRC += $(SRC_OBJ)

SRC += $(SRC_INTER)

SRC += $(SRC_INPUT)

SRC += $(SRC_PARSE)

SRC += $(SRC_OBJ_PARSER)

INC = ./includes/

LIBFT_PATH = ./libft/libft.a

MLX_PATH = ./minilibx/libmlx.a

MLX_PATH_LINUX = ./minilibx_linux/libmlx_Linux.a

LIBALGEBRA_PATH = ./libalgebra/libalgebra.a

LIBBMP_PATH = ./libbmp/libbmp.a

OBJ = $(SRC:%.c=%.o)

CC = gcc

FLAGS = -O3 -Wall -Werror -Wextra

MKDIR = $(shell mkdir image 2> /dev/null)

all: $(NAME)

ifeq ($(OS), Darwin)
$(NAME): $(OBJ) $(LIBFT_PATH) $(MLX_PATH) $(LIBALGEBRA_PATH) $(LIBBMP_PATH) $(MKDIR)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT_PATH) $(LIBALGEBRA_PATH) $(MLX_PATH) $(LIBBMP_PATH) -o $(NAME) -framework OpenGl -framework AppKit
endif

ifeq ($(OS), Linux)
$(NAME): $(OBJ) $(LIBFT_PATH) $(MLX_PATH_LINUX) $(LIBALGEBRA_PATH) $(LIBBMP_PATH) $(MKDIR)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT_PATH) $(LIBALGEBRA_PATH) $(MLX_PATH_LINUX) $(LIBBMP_PATH) -o $(NAME) -lXext -lX11 -lm -lpthread
endif

%.o: $(SRC_PATH)%.c $(INC)rtv1.h
	$(CC) $(FLAGS) -I $(INC) -c $(SRC_ROOT)

%.o: $(OBJ_PATH)%.c $(INC)rtv1.h
	$(CC) $(FLAGS) -I $(INC) -c $(SRC_OBJ)

%.o: $(INTER_PATH)%.c $(INC)rtv1.h
	$(CC) $(FLAGS) -I $(INC) -c $(SRC_INTER)

%.o: $(PARSE_PATH)%.c $(INC)rtv1.h
	$(CC) $(FLAGS) -I $(INC) -c $(SRC_PARSE)

%.o: $(INPUT_PATH)%.c $(INC)rtv1.h
	$(CC) $(FLAGS) -I $(INC) -c $(SRC_INPUT})

%.o: $(OBJ_PARSER_PATH)%.c $(INC)rtv1.h
	$(CC) $(FLAGS) -I $(INC) -c $(SRC_OBJ_PARSER})

$(LIBBMP_PATH):
	make -C ./libbmp/

$(LIBALGEBRA_PATH):
	make -C ./libalgebra/

$(LIBFT_PATH):
	make -C ./libft/

$(MLX_PATH):
	make -C ./minilibx/

$(MLX_PATH_LINUX):
	make -C ./minilibx_linux/

clean:
	rm -f $(OBJ)
	make -C ./libft/ clean
	make -C ./minilibx/ clean
	make -C ./libalgebra/ clean
	make -C ./libbmp/ clean

fclean: clean
	rm -f $(NAME)
	make -C ./libft/ fclean
	make -C ./minilibx/ fclean
	make -C ./libalgebra/ fclean
	make -C ./libbmp/ fclean

re: fclean all

.PHONY: all clean fclean re
