# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/13 20:05:41 by arcebria          #+#    #+#              #
#    Updated: 2025/02/18 19:17:02 by arcebria         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = src/main.c src/manage_errors.c src/utils.c src/philos_routine.c src/monitor.c
OBJS = $(SRCS:.c=.o)

INCLUDE = inc/philosophers.h
CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address


all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A) Makefile
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
		@echo "\033[31mAsunto compilado\033[0m"



%.o: %.c $(INCLUDE)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@echo "\033[31mAsunto eliminado\033[0m"

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean
