# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/07 13:42:30 by jweber            #+#    #+#              #
#    Updated: 2025/06/02 16:18:28 by jweber           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

CC := cc
CFLAGS := -Wall -Wextra -Werror -MMD -MP

LIBFT_DIR := src/libft/

LIBRARY := -lreadline -lft -L $(LIBFT_DIR) 

INCLUDES := -I $(LIBFT_DIR)includes -I includes/

PRINTING_DIR := src/printing/
PRINTING_FILES := print_error.c \


PARSING_DIR := src/parsing/
PARSING_FILES := lexer.c \
				 init_args.c \
				 get_next_token.c \
				 ft_split_args.c \
				 ft_strstr_args.c \

AST_DIR := src/ast/
AST_FILES := print_tree.c \
			 tree_operations.c \
			 free_everything.c \

EXECUTION_DIR := src/execution/
EXECUTION_FILES := exec_command.c \

C_FILES := minishell.c \
		   $(addprefix $(PARSING_DIR),$(PARSING_FILES)) \
		   $(addprefix $(PRINTING_DIR), $(PRINTING_FILES)) \
		   $(addprefix $(AST_DIR), $(AST_FILES))\
		   $(addprefix $(EXECUTION_DIR), $(EXECUTION_FILES))\

OBJ_DIR := .obj/
OBJ_DIR_DEBUG = .obj_debug/
OBJ_FILES := $(addprefix $(OBJ_DIR), $(C_FILES:.c=.o))
D_FILES := $(OBJ_FILES:.c=.o)

.PHONY : all clean fclean re debug debug_clean debug_fclean debug_re

all: makelibft $(NAME)

makelibft:
	$(MAKE) -C $(LIBFT_DIR)

git_init :
	git submodule update --init

git_update : 
	git submodule update --init --remote --recursive

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBRARY)

$(OBJ_DIR)%.o : %.c | $(OBJ_DIR)$(PARSING_DIR) $(OBJ_DIR)$(PRINTING_DIR) $(OBJ_DIR)$(AST_DIR) $(OBJ_DIR)$(EXECUTION_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)$(AST_DIR):
	mkdir -p $@

$(OBJ_DIR)$(PARSING_DIR):
	mkdir -p $@

$(OBJ_DIR)$(PRINTING_DIR):
	mkdir -p $@

$(OBJ_DIR)$(EXECUTION_DIR):
	mkdir -p $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean:
	$(MAKE) clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

debug:
	rm -f $(NAME)
	$(MAKE) CFLAGS="$(CFLAGS) -g3" OBJ_DIR="$(OBJ_DIR_DEBUG)" all

debug_clean:
	$(MAKE) CFLAGS="$(CFLAGS) -g3" OBJ_DIR="$(OBJ_DIR_DEBUG)" clean

debug_fclean:
	$(MAKE) CFLAGS="$(CFLAGS) -g3" OBJ_DIR="$(OBJ_DIR_DEBUG)" fclean

debug_re:
	$(MAKE) CFLAGS="$(CFLAGS) -g3" OBJ_DIR="$(OBJ_DIR_DEBUG)" re
