/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:46:41 by cviel             #+#    #+#             */
/*   Updated: 2025/08/05 18:30:33 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include <unistd.h>
# include "ft_vectors.h"

# define NB_T_TYPE 7

typedef enum e_type
{
	SUBSHELL,
	COMMAND,
	PIPE,
	OR,
	AND,
	SEQUENCE,
	END_SUBSHELL,
	END_LINE
}	t_type;

typedef enum e_dir
{
	IN,
	OUT,
	APPEND,
	HEREDOC,
	NOT_DIR
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

typedef struct s_subargs
{
	struct s_ast	*sub;
	t_vector		dir_args;
}	t_subargs;

typedef union u_args
{
	t_comargs		com_args;
	t_opargs		op_args;
	t_subargs		sub_args;
}	t_args;

typedef struct s_ast
{
	t_type	type;
	t_args	arguments;
}	t_ast;

void	free_dirargs(t_vector *dirargs_ptr);
void	free_command_content(t_vector *content_ptr);
void	free_tree(t_ast **root);
t_type	get_type(t_vector tokens, size_t ind);
t_dir	get_dir(t_vector tokens, size_t ind);
int		fill_command(t_comargs *p_com_args, t_vector tokens, size_t *ind);
int		fill_redir(t_vector *p_dir_args,
			t_vector tokens, size_t *ind, t_dir dir);
t_ast	*create_ast(t_vector tokens, t_type max_prio, size_t *ind);
char	*print_type(t_type type);
char	*print_redir_in_out(t_dir dir);
void	print_tree(t_ast *root, size_t depth);

#endif
