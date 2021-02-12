# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/02 20:44:56 by ejolyn            #+#    #+#              #
#    Updated: 2021/02/11 13:31:02 by ejolyn           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= 	main.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
				map_maker.c parser_main.c parse_textures_color_res.c init.c move_player.c save_screen.c \
				sprites.c main_raycast.c different_utils.c different_utils2.c

OBJS		=	${SRCS:.c=.o}

NAME		=	cub3D

INCLUDES	= 	cub3d.h

MAKELIB		=	@make -C ./libft

MAKELIBBONUS	=	@make bonus -C ./libft

MAKEMLX			= @make -C ./mlx

RM			=	rm -f

CC			=	gcc

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

$(NAME): $(OBJS) $(INCLUDES)
		$(MAKELIB)
		$(MAKELIBBONUS)
		$(MAKEMLX)
		mv -f ./libft/libft.a ./
		mv -f ./mlx/libmlx.dylib ./
		$(CC) $(OBJS) -Lmlx -lmlx -L. -lft -framework OpenGL -framework AppKit -o ${NAME}

all:		${NAME}

clean:
			${RM} ${OBJS}
			@make clean -C ./libft

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all bonus clean fclean re
