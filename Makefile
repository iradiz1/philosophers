# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hzibari <hzibari@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/10 11:49:26 by hzibari           #+#    #+#              #
#    Updated: 2024/04/26 13:31:31 by hzibari          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

SRCS	=	main.c \
			utils.c \
			init.c \
			start_sim.c \
			routines.c \
			monitor.c

OFILES	=	$(SRCS:.c=.o)

CC		=	cc
RM		=	-rm -f
CFLAGS	=	-Wall -Werror -Wextra #-fsanitize=thread -pthread

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