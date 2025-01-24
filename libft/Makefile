# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhervoch <jhervoch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/23 14:19:41 by jhervoch          #+#    #+#              #
#    Updated: 2025/01/23 17:24:19 by jhervoch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COLORS
RESET = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m
RED_BG = \e[1;41m
GREEN_BG = \e[1;42m

# VARIABLES
CC			:=	cc -g
CFLAGS		:=	-Wall -Wextra -Werror
RM			:=	rm -f
NAME		:=	libft.a

INC_DIR 	:= ./includes/
SRCS_DIR	:= ./src/
CPPFLAGS 	:= $(addprefix -I, $(INC_DIR))

#CHAR
SRCS		:= 	$(addprefix $(SRCS_DIR)char/ft_, isalnum isalpha isascii isdigit isprint tolower toupper)
#CONVERT
SRCS		+= 	$(addprefix $(SRCS_DIR)convert/ft_,atoi atoier atol itoa)
#LST
SRCS		+= 	$(addprefix $(SRCS_DIR)lst/ft_,lstadd_back lstadd_front lstclear lstdelone lstiter	\
			   	lstlast lstmap lstnew lstsize)
#MEM
SRCS		+= 	$(addprefix $(SRCS_DIR)mem/ft_,bzero calloc memchr memcmp memmove memset memcpy)
#PRINTF
SRCS		+= 	$(addprefix $(SRCS_DIR)printf/ft_,printf putcounthex_fd putcountunbr_fd putcountcstr					\
				putcountnbr_fd putcountptr)
#PUT
SRCS		+= 	$(addprefix $(SRCS_DIR)put/ft_,putchar_fd putendl_fd putnbr_fd putstr_fd)
#STR
SRCS		+=  $(addprefix $(SRCS_DIR)str/ft_,split strchr strdup striteri strjoin strlcat strlcpy strlen strmapi	\
			   	strcmp strncmp strnstr strrchr strtrim substr) 
#GET_NEXT_LINE				
SRCS		+=  $(addprefix $(SRCS_DIR)ft_,get_next_line)

SRCS		:= $(addsuffix .c, $(SRCS))


OBJS		:= $(SRCS:.c=.o)


# VARIABLES FOR PROGRESS BAR
TOTAL_OBJS  := $(shell echo $(OBJS)| wc -w)
COMPILED_OBJS = 0

all		: 	$(NAME) 

$(NAME) : 	$(OBJS)
			@ar crs $(NAME) $^ 
			@echo "$(GREEN_BG)\t[LIBFT COMPILED]$(RESET)"

# PROGRESS BAR
define PROGRESS_BAR
	$(eval COMPILED_OBJS=$(shell echo $$(($(COMPILED_OBJS) + 1))))
	@PROGRESS=$$(($(COMPILED_OBJS) * 100 / $(TOTAL_OBJS))); \
	BAR_WIDTH=30; \
	FILLED_WIDTH=$$(($$PROGRESS * $$BAR_WIDTH / 100)); \
	EMPTY_WIDTH=$$(($$BAR_WIDTH - $$FILLED_WIDTH)); \
	BAR=$$(for i in $$(seq 1 $$FILLED_WIDTH); do echo -n "█"; done); \
	BAR="$$BAR$$(for i in $$(seq 1 $$EMPTY_WIDTH); do echo -n " "; done)"; \
	printf "\r$(GREEN)[$$BAR]$(DEF_COLOR) $$PROGRESS%% "; \
	if [ $$PROGRESS -eq 100 ]; then printf "\n$(RESET)"; fi
endef

$(OBJS): %.o : %.c
			@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
			@$(call PROGRESS_BAR)

clean	:
			@$(RM) $(OBJS)
			@echo "$(RED_BG)[LIBFT OBJS CLEANED!]$(RESET)"

fclean	:	clean
			@$(RM) $(NAME)
			@echo "$(RED_BG)[LIBFT EXEC CLEANED!]$(RESET)"

re		:	fclean all

.PHONY	:	all clean fclean re

