# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/07 13:42:30 by jweber            #+#    #+#              #
#    Updated: 2025/06/12 18:48:40 by jweber           ###   ########.fr        #
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
EXECUTION_FILES := exec_func.c \
				   exec_pipe.c \
				   exec_command.c \
				   child_execution.c \
				   change_fd_redir.c \
				   init_minishell.c \
				   init_env.c \
				   init_path.c \
				   find_command.c \
				   free_minishell.c \


CD_DIR := cd/
CD_FILES := cd.c

ECHO_DIR := echo/
ECHO_FILES := echo.c

ENV_DIR := env/
ENV_FILES := env.c

EXIT_DIR := exit/
EXIT_FILES := exit.c

EXPORT_DIR := export/
EXPORT_FILES := export.c

PWD_DIR := pwd/
PWD_FILES := pwd.c

UNSET_DIR := unset/
UNSET_FILES := unset.c

BUILTIN_DIR := src/builtin/
BUILTIN_FILES := $(addprefix $(CD_DIR),$(CD_FILES)) \
				 $(addprefix $(ECHO_DIR),$(ECHO_FILES)) \
				 $(addprefix $(ENV_DIR),$(ENV_FILES)) \
				 $(addprefix $(EXIT_DIR),$(EXIT_FILES)) \
				 $(addprefix $(EXPORT_DIR),$(EXPORT_FILES)) \
				 $(addprefix $(PWD_DIR),$(PWD_FILES)) \
				 $(addprefix $(UNSET_DIR),$(UNSET_FILES)) \

C_FILES := minishell.c \
		   $(addprefix $(PARSING_DIR),$(PARSING_FILES)) \
		   $(addprefix $(PRINTING_DIR), $(PRINTING_FILES)) \
		   $(addprefix $(AST_DIR), $(AST_FILES)) \
		   $(addprefix $(EXECUTION_DIR), $(EXECUTION_FILES)) \
		   $(addprefix $(BUILTIN_DIR), $(BUILTIN_FILES)) \

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

$(OBJ_DIR)%.o : %.c | $(OBJ_DIR)$(PARSING_DIR) \
					  $(OBJ_DIR)$(PRINTING_DIR) \
					  $(OBJ_DIR)$(AST_DIR) \
					  $(OBJ_DIR)$(EXECUTION_DIR) \
					  $(OBJ_DIR)$(BUILTIN_DIR)$(CD_DIR) \
					  $(OBJ_DIR)$(BUILTIN_DIR)$(ECHO_DIR) \
					  $(OBJ_DIR)$(BUILTIN_DIR)$(ENV_DIR) \
					  $(OBJ_DIR)$(BUILTIN_DIR)$(EXIT_DIR) \
					  $(OBJ_DIR)$(BUILTIN_DIR)$(EXPORT_DIR) \
					  $(OBJ_DIR)$(BUILTIN_DIR)$(PWD_DIR) \
					  $(OBJ_DIR)$(BUILTIN_DIR)$(UNSET_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


$(OBJ_DIR)$(BUILTIN_DIR)$(CD_DIR): 
	mkdir -p $@

$(OBJ_DIR)$(BUILTIN_DIR)$(ECHO_DIR): 
	mkdir -p $@

$(OBJ_DIR)$(BUILTIN_DIR)$(ENV_DIR): 
	mkdir -p $@

$(OBJ_DIR)$(BUILTIN_DIR)$(EXIT_DIR): 
	mkdir -p $@

$(OBJ_DIR)$(BUILTIN_DIR)$(EXPORT_DIR): 
	mkdir -p $@

$(OBJ_DIR)$(BUILTIN_DIR)$(PWD_DIR): 
	mkdir -p $@

$(OBJ_DIR)$(BUILTIN_DIR)$(UNSET_DIR):
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
