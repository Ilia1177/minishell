# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npolack <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/16 16:15:39 by npolack           #+#    #+#              #
#    Updated: 2025/01/27 15:17:32 by npolack          ###   ########.fr        #
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
	RLLIB		= -L./usr/lib/x86_64-linux-gnu/ -lreadline
	INCLUDE		= -I./include -I./libft/includes -I./libft/ -I./usr/lib/
else
	CC			= cc
	RLLIB		= -L/usr/local/opt/readline/lib -lreadline -lhistory
	INCLUDE		= -I/usr/local/opt/readline/include -I./include -I./libft/includes -I./libft/ 
endif


LIBFT		= ./libft/libft.a
SRCS_DIR	= srcs
OBJS_DIR	= objs
C_FLAGS		= -Wall -Wextra -Werror -g

SRCS		=	binary_tree.c\
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
				builtin_cd.c\

SRCS		:= $(addprefix $(SRCS_DIR)/, $(SRCS))

MINISHELL_SRC := $(SRCS_DIR)/minishell.c
MINISHELL_JM_SRC := $(SRCS_DIR)/minishell-jm.c
MINISHELL_NIL_SRC := $(SRCS_DIR)/minishell-nil.c
MINISHELL_OBJ := $(OBJS_DIR)/minishell.o
MINISHELL_JM_OBJ := $(OBJS_DIR)/minishell-jm.o
MINISHELL_NIL_OBJ := $(OBJS_DIR)/minishell-nil.o

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

jm: fclean $(OBJS) $(MINISHELL_JM_OBJ) $(LIBFT)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(C_FLAGS) $(INCLUDE) $^ -o $@
	@echo "Compiled with minishell-jm.c"

nil:fclean $(OBJS) $(MINISHELL_NIL_OBJ) $(LIBFT)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(C_FLAGS) $(INCLUDE) $^ -o $@
	@echo "Compiled with minishell-nil.c"

$(OBJS_DIR)/%.o	: $(SRCS_DIR)/%.c 
	@mkdir -p $(OBJS_DIR)
	$(CC) $(C_FLAGS) $(INCLUDE) -c $< -o $@

$(MINISHELL_OBJ) : $(MINISHELL_SRC)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(C_FLAGS) $(INCLUDE) -c $< -o $@

$(MINISHELL_JM_OBJ) : $(MINISHELL_JM_SRC)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(C_FLAGS) $(INCLUDE) -c $< -o $@

$(MINISHELL_NIL_OBJ) : $(MINISHELL_NIL_SRC)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(C_FLAGS) $(INCLUDE) -c $< -o $@

$(NAME)			:  $(OBJS) $(MINISHELL_OBJ) $(LIBFT)
	@mkdir -p bin
	$(CC) $(C_FLAGS) $(INCLUDE) $^ $(RLLIB) -o $@

$(LIBFT)		:
	make -C libft

clean			:
	@make clean -C libft
	rm -fr $(OBJS_DIR)

fclean			: clean
	@make fclean -C libft
	rm -fr bin

re				: fclean all

.PHONY			: all clean fclean re bonus

