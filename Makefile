# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npolack <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/16 16:15:39 by npolack           #+#    #+#              #
#    Updated: 2025/01/16 18:36:26 by npolack          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bin/minishell

OS := $(shell uname)

ifeq ($(OS), Linux)
	CC		= cc
else
	CC		= clang
endif

INCLUDE		= -I./include -I./libft/includes -I./libft/
LIBFT		=  ./libft/libft.a
SRCS_DIR	= srcs
OBJS_DIR	= objs
C_FLAGS		= -Wall -Wextra -Werror -g 

SRCS		=	minishell.c\
				binarytree.c\	

SRCS		:= $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS		= $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all				: $(NAME) 

$(NAME)			:  $(LIBFT) $(OBJS)
	@mkdir -p bin
	$(CC) $(C_FLAGS) $(INCLUDE) $^ -o $@

$(OBJS_DIR)/%.o	: $(SRCS_DIR)/%.c 
	@mkdir -p $(OBJS_DIR)
	$(CC) $(C_FLAGS) $(INCLUDE) -c $< -o $@

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
