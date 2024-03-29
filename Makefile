# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abayar <abayar@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/26 14:33:38 by olakhdar          #+#    #+#              #
#    Updated: 2022/08/17 19:06:19 by abayar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3D

CC = gcc 

FLAGS =  -Wall -Werror -Wextra -I ./mlx -Lmlx -lmlx -framework OpenGL -framework AppKit

FILES = main.c get_next_line.c get_next_line_utils.c ft_split.c check_walls.c cub_utils.c  rgb_colors.c \
		key_hook.c parse_map.c player.c rays.c check_walls2.c drawing_map.c update_image.c \

all: $(NAME)

$(NAME):
	$(CC) $(FLAGS) $(FILES) -o $(NAME)

clean:
	@rm -f $(NAME)

fclean: clean

re: fclean all
