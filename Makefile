# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npolack <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/16 16:15:39 by npolack           #+#    #+#              #
#    Updated: 2025/01/20 13:51:32 by jhervoch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bin/minishell

OS := $(shell uname)

ifeq ($(OS), Linux)
	CC		= cc
	READLINE = sudo apt-get install libreadline-dev
else
	CC		= clang
	READLINE = brew install readline
endif


INCLUDE		= -I./include -I./libft/includes -I./libft/ -I./usr/lib/
LIBFT		= ./libft/libft.a
SRCS_DIR	= srcs
OBJS_DIR	= objs
C_FLAGS		= -Wall -Wextra -Werror -g
RLLIB		= -L./usr/lib/x86_64-linux-gnu/ -lreadline

SRCS		=	minishell.c\
				binary_tree.c\
				tokenize.c\
				token_lst.c

SRCS		:= $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS		= $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all				: $(NAME) 

$(OBJS_DIR)/%.o	: $(SRCS_DIR)/%.c 
	@mkdir -p $(OBJS_DIR)
	$(CC) $(C_FLAGS) $(INCLUDE) -c $< -o $@

$(NAME)			:  $(OBJS) $(LIBFT)
	@mkdir -p bin
	$(CC) $(C_FLAGS) $(INCLUDE) $^ $(RLLIB) -o $@

$(LIBFT)		:
	make -C libft

clean			:
	make clean -C libft
	rm -fr $(OBJS_DIR)

fclean			: clean
	make fclean -C libft
	rm -fr bin

re				: fclean all

.PHONY			: all clean fclean re bonus
