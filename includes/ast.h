/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-23 13:46:41 by cviel             #+#    #+#             */
/*   Updated: 2025/06/03 16:30:47 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "ft_vectors.h"

typedef enum e_type
{
	SUBSHELL,
	COMMAND,
	PIPE,
	AND,
	OR,
	BACKGROUND,
	SEQUENCE,
	END_SUBSHELL,
	END_LINE
}	t_type;

typedef enum e_dir
{
	NOT_DIR,
	IN,
	OUT,
	APPEND,
	HEREDOC
}	t_dir;

typedef struct s_dirargs
{
	t_dir	dir;
	char	*filename;
}	t_dirargs;

typedef struct s_comargs
{
	t_vector	content;
	t_vector	dir_args;
}	t_comargs;

typedef struct s_opargs
{
	struct s_ast	*left;
	struct s_ast	*right;
}	t_opargs;

typedef union u_args
{
	t_comargs		com_args;
	t_opargs		op_args;
	struct s_ast	*sub_args;
}	t_args;

typedef struct s_ast
{
	t_type	type;
	t_args	arguments;
}	t_ast;

void	free_dirargs(t_vector *dirargs_ptr);
void	free_command_content(t_vector *content_ptr);
void	free_tree(t_ast **root);
void	print_tree(t_ast *root, size_t depth);
t_ast	*create_ast(t_vector tokens, t_type max_prio, size_t *ind);

#endif
