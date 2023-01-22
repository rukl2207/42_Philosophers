# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scornhol <scornhol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/02 11:35:35 by scornhol          #+#    #+#              #
#    Updated: 2022/04/02 14:44:59 by scornhol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo_bonus

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -pthread
RM		=	rm -f

FILES	= 	${shell find ./source_bonus -name "*.c"}
SRC		= 	$(FILES)
OBJ		=	$(patsubst %.c,%.o,$(SRC))
HEAD	=	./include_bonus/philo_bonus.h
INC		=	-I$(HEAD)

.PHONY:		all clean fclean re norm ac bonus rebonus

all:		$(NAME)

$(NAME):	$(OBJ) $(HEAD)
			@$(CC) $(CFLAGS) $(INC) $(OBJ) -o $(NAME)
			@echo "\033[32m[$(NAME)] bonus part compiled."

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

bonus:		all

rebonus:	re