# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/08 12:17:17 by eribeiro          #+#    #+#              #
#    Updated: 2022/07/25 14:08:01 by eribeiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D

CC = gcc
INC = cub.h
CFLAGS	=	-Wall -Wextra -Werror -g
IFLAGS = -I. -I./libft -I./mlx_linux
MFLAGS	= -L./mlx_linux -lmlx_Linux -lXext -lX11
MLX_DIR = ./mlx_linux
MLX = libmlx.a

SRC		=	main.c\
			map_parsing_3.c\
			map_parsing_2.c\
			map_parsing.c\
			cub.c\
			errors.c\
			ft_split.c\
			get_next_line.c\
			get_next_line_utils.c\
			free.c\
			ft_atoi.c\
			paths.c\
			ft_strlcpy.c\
			initialize.c\
			keycode.c\
			texture.c\
			ray.c\
			ray_h.c\
			ray_v.c\
			put_colors.c\

			
OBJ		=	$(SRC:%.c=%.o)

%.o: %.c $(INC)
			$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@


$(NAME):	$(OBJ)
			$(MAKE) -C ./$(MLX_DIR)
			cp ./$(MLX_DIR)/$(MLX) .
			$(CC) $(CFLAGS) $(OBJ) $(IFLAGS) $(LFLAGS) $(MFLAGS) -lm -o $@

all:		$(NAME)

clean:
			rm -rf $(OBJ)

fclean:		clean
			$(MAKE) -C ./$(MLX_DIR) clean
			rm -rf $(MLX)
			rm -rf $(NAME)

re:			fclean all

.PHONY: all clean fclean re
