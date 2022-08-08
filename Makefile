# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olakhdar <olakhdar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/26 14:33:38 by olakhdar          #+#    #+#              #
#    Updated: 2022/08/08 10:38:21 by olakhdar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3D

CC = gcc 

FLAGS =  -Wall -Werror -Wextra -lmlx -framework OpenGL -framework AppKit -g#3 -fsanitize=address 

FILES = main.c get_next_line.c get_next_line_utils.c ft_split.c check_walls.c cub_utils.c  rgb_colors.c \
		key_hook.c parse_map.c player.c \

all: $(NAME)

$(NAME):
	$(CC) $(FLAGS) $(FILES) -o $(NAME)

clean:
	@rm -f $(NAME)

fclean: clean

re: fclean all
