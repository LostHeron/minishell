/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-09 12:28:46 by cviel             #+#    #+#             */
/*   Updated: 2025-05-09 12:28:46 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

typedef enum e_type
{
	SUBSHELL,
	COMMAND,
	PIPE,
	AND,
	OR,
	BACKGROUND,
	SEQUENCE,
	END_SUBSHELL
}	t_type;

typedef enum e_dir
{
	IN,
	OUT,
	APPEND
}	t_dir;

typedef struct s_dirargs
{
	t_dir				dir;
	char				*filename;
	struct s_dirargs	*next;
}	t_dirargs;

typedef struct s_comargs
{
	char		**content;
	t_dirargs	*dir_args;
}	t_comargs;

typedef struct s_opargs
{
	struct s_ast	*left;
	struct s_ast	*right;
}	t_opargs;

typedef union u_args
{
	t_comargs		*com_args;
	t_opargs		op_args;
	struct s_ast	*sub_args;
}	t_args;

typedef struct s_ast
{
	t_type	type;
	t_args	arguments;
}	t_ast;

t_ast	*create_tree(char **av, t_type max_prio, int *ind);
void	print_tree(t_ast *root, int depth);
void	free_tree(t_ast **root);
int		get_ast(char **tokens);

#endif
