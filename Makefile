#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/27 17:05:05 by vtlostiu          #+#    #+#              #
#    Updated: 2019/04/27 17:05:07 by vtlostiu         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = fractol

OBJ_PATH = obj
SRC_PATH = src

SRC_N 	= main.c \
	error_messages.c \
	choose_color_scheme.c \
	color.c \
	control.c \
	count_fractals.c \
	draw_fractals.c \
	init_fractals.c \
	threads.c

INC = -I ./inc -I ./libft/includes/

CC = gcc -g

FLAG = -Wall -Wextra -Werror -pthreads

SRC = $(addprefix ./$(SRC_PATH)/, $(SRC_N))

OBJ = $(addprefix ./$(OBJ_PATH)/, $(SRC_N:.c=.o))

.PHONY: all clean fclean re 

./$(OBJ_PATH)/%.o : ./$(SRC_PATH)/%.c
	$(CC) $(INC) -c $< -o $@

all: $(NAME)

$(NAME): objdir $(OBJ)
		@make -C libft/
		$(CC) -o $(NAME) $(OBJ) $(INC) -L libft/ -lft  -lm -lmlx -framework OpenGL -framework AppKit
		@echo "        \033[0;34m FRACTOL \033[0;35m"
		@echo "	\033[0;34m FRACTOL     \033[0;35m"
		@echo "	\033[0;33m FRACTOL   \033[0;35m"
		@echo "	\033[0;33m FRACTOL     \033[0;35m"
		@echo "	\033[0;33m FRACTOL     \033[0;35m"

objdir:
	mkdir -p $(OBJ_PATH)

clean:
	@rm -rf $(OBJ)
	@make -C libft/ clean
	@echo "\033[37;1;41m CLEAN DONE!!!!!!!! \033[0m"

fclean: clean
	@rm -f $(NAME)
	@make -C libft/ fclean
	@echo "\033[37;1;41m C_FCLEAN DONE_!!!!!!!! \033[0m"

re:	fclean all
