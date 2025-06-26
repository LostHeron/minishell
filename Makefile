# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/07 13:42:30 by jweber            #+#    #+#              #
#    Updated: 2025/06/26 13:45:09 by jweber           ###   ########.fr        #
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
				  print_env.c \
				  print_path.c \

HANDLE_SIGNALS_DIR := src/handle_signals/
HANDLE_SIGNALS_FILES := init_signals.c \

PARSING_DIR := src/parsing/
PARSING_FILES := check_error_syntax.c \
				 check_parenthesis.c \
				 lexer.c \
				 init_args.c \
				 get_next_token.c \
				 ft_split_args.c \
				 ft_strstr_args.c \

AST_DIR := src/ast/
AST_FILES := print_tree.c \
			 tree_operations.c \
			 free_everything.c \

EXECUTION_DIR := src/execution/
EXECUTION_FILES := exec_func.c \
				   exec_or.c \
				   exec_and.c \
				   exec_pipe.c \
				   exec_command.c \
				   child_execution.c \
				   call_builtins.c \
				   change_fd_redir.c \
				   init_minishell.c \
				   init_env.c \
				   init_path.c \
				   init_builtins.c \
				   swap_fds.c \
				   find_command.c \
				   free_minishell.c \

BUILTINS_DIR := src/builtins/
BUILTINS_FILES := builtin_cd.c \
				  builtin_cd_get_path_len_name.c \
				  builtin_cd_without_path.c \
				  builtin_echo.c \
				  builtin_env.c \
				  builtin_exit.c \
				  builtin_export.c \
				  builtin_export_with_args.c \
				  export_from_string.c \
				  get_new_key_value.c \
				  add_new_env.c \
				  builtin_pwd.c \
				  builtin_unset.c \

EXPAND_DIR := src/expand/
EXPAND_FILES := expand.c \
				expand_variables.c \
				rebuild_elem.c \
				split_elem.c \
				expand_redir.c \
				rebuild_filename.c \

C_FILES := minishell.c \
		   $(addprefix $(PARSING_DIR),$(PARSING_FILES)) \
		   $(addprefix $(PRINTING_DIR), $(PRINTING_FILES)) \
		   $(addprefix $(AST_DIR), $(AST_FILES)) \
		   $(addprefix $(EXECUTION_DIR), $(EXECUTION_FILES)) \
		   $(addprefix $(BUILTINS_DIR), $(BUILTINS_FILES)) \
		   $(addprefix $(EXPAND_DIR), $(EXPAND_FILES)) \
		   $(addprefix $(HANDLE_SIGNALS_DIR), $(HANDLE_SIGNALS_FILES)) \

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

$(OBJ_DIR)%.o : %.c | $(OBJ_DIR)$(PARSING_DIR) $(OBJ_DIR)$(PRINTING_DIR) $(OBJ_DIR)$(AST_DIR) $(OBJ_DIR)$(EXECUTION_DIR) $(OBJ_DIR)$(BUILTINS_DIR) $(OBJ_DIR)$(EXPAND_DIR) $(OBJ_DIR)$(HANDLE_SIGNALS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)$(HANDLE_SIGNALS_DIR):
	mkdir -p $@

$(OBJ_DIR)$(EXPAND_DIR):
	mkdir -p $@

$(OBJ_DIR)$(BUILTINS_DIR):
	mkdir -p $@

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
