# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malluin <malluin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/22 14:56:26 by malluin           #+#    #+#              #
#    Updated: 2019/06/03 09:33:33 by ccepre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf 

LIB_PATH = ./libft
HEADER_PATH = ./includes
SRC_PATH = ./srcs
OBJ_PATH = ./obj

CC = gcc #-fsanitize=address
CCFLAGS = -lmlx -framework OpenGL -framework AppKit #-Wall -Wextra -Werror
CPPFLAGS = -I $(HEADER_PATH) -MMD
LIBFLAGS = -L $(LIB_PATH) -lft -lncurses

HEAER_NAME = fdf.h\
			 ft_printf.h\
			 libft.h\
			 get_next_line.h

SRC_NAME = main.c\
		   key_functions.c\
		   map_functions.c\
		   draw_funcions.c\
		   parsing.c\
		   projection.c\
		   actions.c 

OBJ_NAME = $(SRC_NAME:.c=.o)
SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

HEADER = $(addprefix $(HEADER_PATH)/,$(HEADER_NAME))

all: lib $(NAME)

$(NAME): $(OBJ) $(LIB_PATH)/libft.a 
	$(CC) $(CCFLAGS) $(LIBFLAGS) $^ -o $@
	@echo "fdf has been well compiled"

lib:
	@make -C libft/

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	$(CC) $(CCFLAGS) $(CPPFLAGS) -o $@ -c $<

$(OBJ_PATH):
	@mkdir $(OBJ_PATH) 2> /dev/null || true

clean:
	@make clean -C libft/
	rm -f $(OBJ) $(OBJ:.o=.d)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean:	clean
	@make fclean -C libft/
	@rm -f $(NAME)
	@rm -r $(OBJ_PATH)

re: fclean
	$(MAKE) all

norme:
	norminette $(SRC)
	norminette $(INCLUDES)

san : lib $(OBJ)
	gcc -g3 -fsanitize=address -o $(NAME) $(OBJ) $(CCFLAGS) $(LIBFLAGS) $(CPPFLAGS)

.PHONY: lib make clean fclean re

-include $(OBJ:.o=.d)
