# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/02 20:44:56 by ejolyn            #+#    #+#              #
#    Updated: 2020/12/19 19:01:31 by ejolyn           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= 	main.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
				map_maker.c map_validator.c

OBJS		=	${SRCS:.c=.o}

NAME		=	cub3d.out

INCLUDES	= 	cub3d.h

RM			=	rm -f

CC			=	gcc

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

$(NAME): $(OBJS) $(INCLUDES)
		$(CC) $(OBJS) -L. -lmlx -L. -lft -framework OpenGL -framework AppKit -o ${NAME}

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all bonus clean fclean re
