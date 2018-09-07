#  ************************************************************************** #
#                                                           LE - /            #
#                                                               /             #
#    Makefile                                         .::    .:/ .      .::   #
#                                                  +:+:+   +:    +:  +:+:+    #
#    By: rlossy <rlossy@student.le-101.fr>          +:+   +:    +:    +:+     #
#                                                  #+#   #+    #+    #+#      #
#    Created: 2018/09/07 12:17:29 by rlossy       #+#   ##    ##    #+#       #
#    Updated: 2018/09/07 12:17:29 by rlossy      ###    #+. /#+    ###.fr     #
#                                                          /                  #
#                                                         /                   #
#  ************************************************************************** #

NAME		=	libbmp.a
HEADER		=   ./includes/
FILENAMES   =   decode/decode.c decode/header.c decode/rgb_decode.c
FILENAMES   +=  encode/encode.c encode/header.c encode/rgb_encode.c
FILENAMES   +=  shared/bitmap.c shared/check.c shared/utils.c

OBJECTS		=	$(addprefix build/, $(FILENAMES:.c=.o))

LOADIR		=	../extra/Progress_Bar-for-Makefile
LOADF		=	$(LOADIR)/loading.sh

.PHONY: all clean fclean re


all: $(NAME)


clean:
		@echo "\033[31m"
		@sh $(LOADF) $@ r n $(NAME)
		@rm -rf build/
		@printf "\n\033[1m\033[34m\t\t\t\t⥷ $(NAME)⭃\tObject Files\033[0m \
		\033[1m⟿ \t\033[31mDeletion Success\033[0m ✅\n"

fclean: clean
		@echo "\033[31m"
		@sh $(LOADF) $@ r n $(NAME)
		@rm -f $(NAME)
		@printf "\n\033[1m\033[34m\t\t\t\t⥷ $(NAME)⭃\tCompiled Files\033[0m \
		\033[1m⟿ \t\033[31mDeletion Success\033[0m ✅\n"

re:
		@$(MAKE) fclean
		@$(MAKE) all

build:
		@echo "\033[32m"
		@mkdir build/
		@mkdir build/decode
		@mkdir build/encode
		@mkdir build/shared

$(NAME): $(OBJECTS)
		@printf "\n\033[1m\033[34m\t\t\t\t⥷ $(NAME)⭃\tObject Files\033[0m \
		\033[1m⟿ \t\033[32mCreation Success\033[0m ✅\n"
		@echo "\033[45m\033[30m"
		@sh $(LOADF) $@ a n
		@echo "\033[0m"
		@ar crs $@ $(OBJECTS)
		@printf "\n\033[1m\033[34m\t\t\t\t⥷ $@⭃ \tProject\t\t\033[0m\033[1m⟿ \
		\033[32mCreation Success\033[0m ✅\n"

build/%.o: srcs/%.c $(HEADER) | build
	@sh $(LOADF) $< o y
	@gcc $(FLAGS) $(LIB_INC) -I $(HEADER) -c $< -o $@
