# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   Makefile                                           :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: scornhol <scornhol@student.21-school.ru>   +#+  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2022/04/01 20:56:04 by scornhol          #+#    #+#             #
#   Updated: 2022/04/01 20:56:04 by scornhol         ###   ########.fr       #
#                                                                            #
# ************************************************************************** #

NAME	=	philo

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -pthread
RM		=	rm -f

FILES	= 	${shell find ./source -name "*.c"}
SRC		= 	$(FILES)
OBJ		=	$(patsubst %.c,%.o,$(SRC))
HEAD	=	./include/philo.h
INC		=	-I$(HEAD)

.PHONY:		all clean fclean re norm ac

all:		$(NAME)

$(NAME):	$(OBJ) $(HEAD)
			@$(CC) $(CFLAGS) $(INC) $(OBJ) -o $(NAME)
			@echo "\033[32m[$(NAME)] mandatory part compiled."

%.o:		%.c
			@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
			@$(RM) $(OBJ)
			@echo "\033[32m[$(NAME)] removed object files."

fclean:		clean
			@$(RM) $(NAME)
			@echo "\033[32m[$(NAME)] removed executable files."

re:			fclean all

ac:			all clean

norm:
			norminette
