# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npolack <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/16 16:15:39 by npolack           #+#    #+#              #
#    Updated: 2025/02/27 13:01:33 by jhervoch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COLORS
RESET = \033[0;39m
CYAN = \e[5;36m
COLOR = \e[38;5;206m

NAME 		= bin/minishell
NAME_BONUS 	= bin/minishell_bonus

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

SRCS		=	binary_tree/binary_tree.c\
				binary_tree/binary_tree_fd.c\
				builtins/builtin_utils.c\
				builtins/change_dir.c\
				builtins/echo.c\
				builtins/exit.c\
				builtins/export.c\
				builtins/unset.c\
				exec/exec.c\
				exec/exec_tree.c\
				exec/exec_utils.c\
				exec/exec_utils_supp.c\
				exec/exec_utils_supp2.c\
				minishell_runtime/cleanup.c\
				minishell_runtime/cleanup_supp.c\
				minishell_runtime/debug.c\
				minishell_runtime/minishell.c\
				minishell_runtime/prompt.c\
				minishell_runtime/signals.c\
				minishell_runtime/signals_utils.c\
				minishell_runtime/utils.c\
				parsing/lst_iter_func.c\
				parsing/lst_utils.c\
				parsing/parsing.c\
				parsing/quote_utils.c\
				parsing/syntax.c\
				parsing/syntax_utils.c\
				rdir_and_arg/expand.c\
				rdir_and_arg/expand_utils.c\
				rdir_and_arg/heredoc.c\
				rdir_and_arg/heredoc_utils.c\
				rdir_and_arg/redir.c\
				rdir_and_arg/wildcards.c\
				rdir_and_arg/wildcards_search.c\
				rdir_and_arg/wildcards_utils.c\
				tokenize/make_elem.c\
				tokenize/token_tab.c\
				tokenize/token_utils.c\
				tokenize/tokenize.c\

SRCS		:= $(addprefix $(SRCS_DIR)/, $(SRCS))

OBJS		= $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
DEPS = $(OBJS:%.o=%.d)

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

bonus			: $(NAME_BONUS)

$(OBJS_DIR)/%.o	: $(SRCS_DIR)/%.c 
	@mkdir -p $(dir $@)
	@$(CC) $(C_FLAGS) $(INCLUDE) -MMD -c $< -o $@

$(NAME)			:  $(OBJS) $(LIBFT)
	@mkdir -p bin
	@$(CC) $(C_FLAGS) $(INCLUDE) $^ $(RLLIB) -o $@

$(NAME_BONUS)			:  $(OBJS) $(LIBFT)
	@mkdir -p bin
	@$(CC) $(C_FLAGS) $(INCLUDE) $^ $(RLLIB) -o $@

$(LIBFT)		:
	@make -C libft --no-print-directory

clean			:
	@make clean -C libft
	rm -fr $(OBJS_DIR)

fclean			: clean
	@make fclean -C libft
	rm -fr bin

re				: fclean all

.PHONY			: all clean fclean re bonus

-include $(DEPS)
