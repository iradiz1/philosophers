# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hzibari <hzibari@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/10 11:49:26 by hzibari           #+#    #+#              #
#    Updated: 2024/04/10 12:08:25 by hzibari          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

SRCS	=	utils.c

OFILES	=	$(SRCS:.c=.o)

CC		=	cc
RM		=	-rm -f
CFLAGS	=	-Wall -Werror -Wextra

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