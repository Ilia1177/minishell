# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npolack <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/16 16:15:39 by npolack           #+#    #+#              #
#    Updated: 2025/01/24 22:59:36 by ilia             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COLORS
RESET = \033[0;39m
CYAN = \e[5;36m
COLOR = \e[38;5;206m

NAME = bin/minishell

OS := $(shell uname)

ifeq ($(OS), Linux)
	CC			= cc
	READLINE 	= sudo apt-get install libreadline-dev
	RLLIB		= -L./usr/lib/x86_64-linux-gnu/ -lreadline
	INCLUDE		= -I./include -I./libft/includes -I./libft/ -I./usr/lib/
else
	CC			= cc
	READLINE 	= brew install readline
	#RLLIB		= -L./usr/local/Cellar/readline/8.2.13/lib/ -L./usr/local/opt/readline -lreadline
	RLLIB		= -I./usr/local/opt/readline -lreadline
	INCLUDE		=  -I./include -I./libft/includes -I./libft/ 
endif


LIBFT		= ./libft/libft.a
SRCS_DIR	= srcs
OBJS_DIR	= objs
C_FLAGS		= -Wall -Wextra -Werror -g

SRCS		=	minishell.c\
				binary_tree.c\
				tokenize.c\
				token_tab.c\
				token_utils.c\
				lst_utils.c\
				debug.c\
				parsing.c\
				cleanup.c\
				exec_utils.c\
				exec.c\
				signals.c\

SRCS		:= $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS		= $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

msg				:
	@echo "$(COLOR)"
	@echo "███    ███ ██ ███    ██ ██ ███████ ██   ██ ███████ ██      ██"
	@echo "████  ████ ██ ████   ██ ██ ██      ██   ██ ██      ██      ██"
	@echo "██ ████ ██ ██ ██ ██  ██ ██ ███████ ███████ █████   ██      ██"
	@echo "██  ██  ██ ██ ██  ██ ██ ██      ██ ██   ██ ██      ██      ██"
	@echo "██      ██ ██ ██   ████ ██ ███████ ██   ██ ███████ ███████ ███████"
	@echo "$(RESET)"
	@make all --no-print-directory

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

