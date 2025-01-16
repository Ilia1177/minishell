# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npolack <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/16 16:15:39 by npolack           #+#    #+#              #
#    Updated: 2025/01/16 17:47:46 by npolack          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bin/minishell

OS := $(shell uname)

ifeq ($(OS), Linux)
	CC		= cc
else
	CC		= clang
endif

SRCS_DIR	= srcs
OBJS_DIR	= objs
C_FLAGS		= -Wall -Wextra -Werror -g 

SRCS		=	minishell.c\

SRCS		:= $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS		= $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all				: $(NAME) 

$(OBJS_DIR)/%.o	: $(SRCS_DIR)/%.c 
	@mkdir -p $(OBJS_DIR)
	$(CC) $(C_FLAGS) -c $< -o $@

$(NAME)			: $(OBJS)
	@mkdir -p bin
	$(CC) $(C_FLAGS) $^ -o $@ $(LIBS)

clean			:
	rm -fr $(OBJS_DIR)

fclean			: clean
	rm -fr bin

re				: fclean all

.PHONY			: all clean fclean re bonus
