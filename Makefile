# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/07 13:42:30 by jweber            #+#    #+#              #
#    Updated: 2025/05/13 18:14:12 by jweber           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

CC := cc
CFLAGS := -Wall -Wextra -Werror -MMD -MP

LIBFT_DIR := src/libft/

LIBRARY := -lreadline -lft -L $(LIBFT_DIR) 

INCLUDES := -I $(LIBFT_DIR)includes -I includes/

PARSING_DIR := src/parsing/
PARSING_FILES := parsing.c \
				 print_ast.c \

C_FILES := minishell.c \
		   $(addprefix $(PARSING_DIR),$(PARSING_FILES)) \

OBJ_DIR := .obj/
OBJ_FILES := $(addprefix $(OBJ_DIR), $(C_FILES:.c=.o))
D_FILES := $(OBJ_FILES:.c=.o)

.PHONY : all clean fclean re

all: makelibft $(NAME)

makelibft:
	$(MAKE) -C $(LIBFT_DIR)

git_init :
	git submodule update --init

git_update : 
	git submodule update --init --remote --recursive

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBRARY)

$(OBJ_DIR)%.o : %.c | $(OBJ_DIR)$(PARSING_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)$(PARSING_DIR):
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
