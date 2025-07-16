# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/07 13:42:30 by jweber            #+#    #+#              #
#    Updated: 2025/07/15 16:08:30 by jweber           ###   ########.fr        #
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
PARSING_FILES := tokenize.c \
				 line_to_tokens.c \
				 check_errors.c \
				 check_error_syntax.c \
				 check_parenthesis.c \
				 check_after.c \
				 check_after_redir.c \
				 check_before.c \
				 check_before_after.c \
				 prepare_here_docs.c \
				 count_here_doc.c \
				 generate_hd_filename.c \
				 get_here_doc.c \
				 write_to_here_doc.c \
				 get_key.c \
				 get_value.c \
				 get_real_delimiter.c \
				 here_doc_delimited_by_end_of_file.c \
				 here_doc_transform.c \
				 fill_file_expand.c \
				 fill_file_no_expand.c \
				 lexer.c \
				 init_args.c \
				 get_next_token.c \
				 ft_split_args.c \
				 ft_strstr_args.c \

AST_DIR := src/ast/
AST_FILES := print_tree.c \
			 tree_operations.c \
			 free_everything.c \

INIT_DIR := src/init/
INIT_FILES := init_minishell.c \
			  init_env.c \
			  add_node_lst.c \
			  init_builtins.c \
			  init_cwd_name.c \
			  cwd_and_pwd_env_match.c \

FREEING_DIR := src/freeing/
FREEING_FILES := free_minishell.c \
				 free_env.c \

EXECUTION_DIR := src/execution/
EXECUTION_FILES := exec_func.c \
				   exec_or.c \
				   exec_and.c \
				   exec_pipe.c \
				   exec_command.c \
				   exec_sequence.c \
				   exec_background.c \
				   exec_subshell.c \
				   exit_child.c \
				   child_execution.c \
				   parent_execution.c \
				   change_fd_pipe.c \
				   close_fd1.c \
				   case_forking.c \
				   case_no_forking.c \
				   restore_fds.c \
				   wait_children.c \
				   get_path.c \
				   call_builtins.c \
				   change_fd_redir.c \
				   close_here_doc_fds.c \
				   swap_fds.c \
				   find_command.c \

BUILTINS_DIR := src/builtins/
BUILTINS_FILES := builtin_cd.c \
				  builtin_cd_get_path_len_name.c \
				  builtin_cd_without_path.c \
				  builtin_echo.c \
				  builtin_env.c \
				  builtin_exit.c \
				  builtin_export.c \
				  builtin_export_with_args.c \
				  builtin_export_no_args.c \
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
		   $(addprefix $(INIT_DIR), $(INIT_FILES)) \
		   $(addprefix $(FREEING_DIR), $(FREEING_FILES)) \

OBJ_DIR := .obj/
OBJ_DIR_DEBUG = .obj_debug/
OBJ_FILES := $(addprefix $(OBJ_DIR), $(C_FILES:.c=.o))
D_FILES := $(OBJ_FILES:.o=.d)

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

-include $(D_FILES)

$(OBJ_DIR)%.o : %.c | $(OBJ_DIR)$(PARSING_DIR) $(OBJ_DIR)$(PRINTING_DIR) $(OBJ_DIR)$(AST_DIR) $(OBJ_DIR)$(EXECUTION_DIR) $(OBJ_DIR)$(BUILTINS_DIR) $(OBJ_DIR)$(EXPAND_DIR) $(OBJ_DIR)$(HANDLE_SIGNALS_DIR) $(OBJ_DIR)$(INIT_DIR) $(OBJ_DIR)$(FREEING_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)$(FREEING_DIR):
	mkdir -p $@

$(OBJ_DIR)$(INIT_DIR):
	mkdir -p $@

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
