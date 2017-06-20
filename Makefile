# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rschramm <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/10 14:23:11 by rschramm          #+#    #+#              #
#    Updated: 2017/03/21 10:39:38 by rschramm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

FLAG += -Wall -Werror -Wextra

SRC = ./srcs/main.c \
	  ./srcs/cd.c \
	  ./srcs/cd2.c \
	  ./srcs/env.c \
	  ./srcs/env_mod.c \
	  ./srcs/fork.c \
	  ./srcs/get_info.c \
	  ./srcs/path.c \
	  

OBJ = $(SRC:.c=.o)

LIBFT = libft/libftprintf.a \

all: $(NAME)

$(NAME): $(OBJ)
	@make re -C libft
	@$(CC) $(FLAG) -o $(NAME) $(SRC) $(LIBFT)

clean:
	@make clean -C libft
	@rm -f $(OBJ)

fclean:
	@make fclean -C libft
	@rm -f $(OBJ)
	@rm -f $(NAME)

re: fclean all
