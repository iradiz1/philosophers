# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: halgordzibari <halgordzibari@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/10 11:49:26 by hzibari           #+#    #+#              #
#    Updated: 2024/04/16 23:49:12 by halgordziba      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

SRCS	=	main.c \
			utils.c \
			init.c \
			start_sim.c \
			routines.c

OFILES	=	$(SRCS:.c=.o)

CC		=	cc
RM		=	-rm -f
# CFLAGS	=	-Wall -Werror -Wextra

all: $(NAME)

$(NAME): ${OFILES}
	$(CC) $(CFLAGS) $(OFILES) -o $(NAME)

%.o: %.c
		$(CC) -c $(CFLAGS) $< -o $@

clean:
		$(RM) $(OFILES)
	
fclean: clean
		$(RM) $(NAME) $(OFILES)

re: fclean all

.PHONY: all clean fclean re