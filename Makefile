# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gumendes <gumendes@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/03 15:17:36 by gumendes          #+#    #+#              #
#    Updated: 2025/05/19 15:53:36 by gumendes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==============================================================================#
#                                  COMPILER AND FLAGS                          #
#==============================================================================#

CC			=	cc
RM			=	rm -rf
CFLAGS		=	-Wall -Wextra -Werror -pthread -g
LDFLAGS		=	-lreadline -lncurses
LEAK		=	-fsanitize=leak

#==============================================================================#
#                                  PATHS       					               #
#==============================================================================#

SRC_PATH		=	srcs
BUILD_PATH		=   .build
INCLUDE_PATH	=	includes

#==============================================================================#
#                                  LIBFT       					               #
#==============================================================================#

LIBFT_PATH		=	libft
LIBFT			=	$(LIBFT_PATH)/libft.a

#==============================================================================#
#                                  INCLUDES			                           #
#==============================================================================#

INCLUDES    =   -I$(INCLUDE_PATH) -I$(LIBFT_PATH)

#==============================================================================#
#                                  PROJECT NAME                                #
#==============================================================================#

NAME		=	minishell

#==============================================================================#
#                                  SOURCE AND OBJECT FILES                     #
#==============================================================================#

SRC_BUILTIN	=	$(addprefix built_in/, cd.c echo.c env.c exit.c export.c pwd.c unset.c)
SRC_CLEANUP	=	$(addprefix clean_up/, free.c)
SRC_COMMAND	=	$(addprefix commands/, executer.c)
SRC_ERRORS	=	$(addprefix err_handling/, errors.c)
SRC_MAIN	=	$(addprefix main/, minishell.c)
SRC_PIPES	=	$(addprefix pipes/, pipe.c)
SRC_REDIR	=	$(addprefix redirections/, input_redir.c output_redir.c redirect.c)
SRC_SIGNALS	=	$(addprefix signals/, signals.c)
SRC_UTILS	=	$(addprefix utils/, cd_utils.c central_utils.c env_utils.c exec_utils.c list_utils.c pipe_utils.c redir_utils.c utils.c)

SRC			=	$(addprefix $(SRC_PATH), $(SRC_BUILTIN) $(SRC_CLEANUP) $(SRC_COMMAND) $(SRC_ERRORS) $(SRC_MAIN) $(SRC_PIPES) $(SRC_REDIR) $(SRC_SIGNALS) $(SRC_UTILS))

OBJ         =   $(SRC:$(SRC_PATH)%.c=$(BUILD_PATH)/%.o)

#==============================================================================#
#                                  RULES                                       #
#==============================================================================#

all: $(NAME)

# Build the libft library
$(LIBFT):
	@if [ ! -d "libft" ]; then make get_libft; fi

get_libft:
	@git clone git@github.com:PTGus/libft.git
	@echo "$(GRN)[LIBFT CLONED]$(END)"
	@$(MAKE) -C $(LIBFT_PATH)

# Build the minishell program
$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LDFLAGS)
	@echo "$(GRN)[PROJECT BUILT]$(END)"

# Rule to create object files in the .build folder
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	@if [ -d "$(BUILD_PATH)" ]; \
		then echo "$(RED)[REMOVED OBJECT FILES]$(END)"; \
		else echo "$(YEL)[NO OBJECTS TO CLEAN]$(END)"; \
	fi
	@$(RM) $(BUILD_PATH)

# Full clean
fclean: clean
	@if [ -f "$(NAME)" ]; \
		then echo "$(RED)[REMOVED EXECUTABLE]$(END)"; \
		$(RM) $(NAME) ; \
		else echo "$(YEL)[EXECUTABLE ALREADY CLEANED]$(END)"; \
	fi
	@if [ -d "$(LIBFT_PATH)" ]; \
		then echo "$(RED)[REMOVED LIBFT]$(END)"; \
		$(RM) $(LIBFT_PATH) ; \
		else echo "$(YEL)[LIBFT ALREADY CLEANED]$(END)"; \
	fi

# Rebuild the project
re: fclean all

# Phony targets
.PHONY: all clean fclean re

#==============================================================================#
#                                  UTILS                                       #
#==============================================================================#

# Colors
#
# Run the following command to get list of available colors
# bash -c 'for c in {0..255}; do tput setaf $c; tput setaf $c | cat -v; echo =$c; done'
#
B		= $(shell tput bold)
BLA		= $(shell tput setaf 16)
RED		= $(shell tput setaf 1)
GRN		= $(shell tput setaf 46)
BRW		= $(shell tput setaf 3)
BLU		= $(shell tput setaf 27)
PRP		= $(shell tput setaf 57)
CYA		= $(shell tput setaf 51)
WHI		= $(shell tput setaf 15)
GREY	= $(shell tput setaf 8)
ORAN	= $(shell tput setaf 202)
YEL		= $(shell tput setaf 226)
D		= $(shell tput sgr0)
BEL		= $(shell tput bel)
CLR		= $(shell tput el 1)
