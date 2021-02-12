# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ejolyn <ejolyn@stud.21-school.ru>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/02 20:44:56 by ejolyn            #+#    #+#              #
#    Updated: 2020/11/04 14:41:31 by ejolyn           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= 	ft_isalnum.c ft_bzero.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_strdup.c ft_strncmp.c \
				ft_memcmp.c ft_strchr.c ft_strrchr.c ft_memccpy.c ft_memchr.c ft_memcpy.c ft_memmove.c ft_memset.c \
				ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_substr.c ft_tolower.c ft_toupper.c ft_atoi.c ft_calloc.c \
				ft_strnstr.c ft_strjoin.c ft_strtrim.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
				ft_putnbr_fd.c ft_split.c \

OBJS		=	${SRCS:.c=.o}

NAME		=	libft.a

BONUS		=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
				ft_lstiter.c ft_lstmap.c \

BONOBJS		=	${BONUS:.c=.o}

INCLUDE		=	libft.h

RM			=	rm -f

AR			=	ar rc

CFLAGS		=	-Wall -Werror -Wextra

.c.o: 		${OBJS} ${INCLUDE}
			gcc ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS} ${INCLUDE}
			${AR} ${NAME} ${OBJS}
			ranlib ${NAME}

all:		${NAME}

bonus:		${BONOBJS} ${OBJS} ${INCLUDE}
			${AR} ${NAME} ${BONOBJS} 
			ranlib ${NAME}

clean:
			${RM} ${OBJS} ${BONOBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all bonus clean fclean re
