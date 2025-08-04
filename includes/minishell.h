/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:39:55 by jweber            #+#    #+#             */
/*   Updated: 2025/08/04 19:50:53 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_vectors.h"
# include "ft_lists_single.h"
# include "ast.h"
# define WHITE_SPACES " \t\n\v\f\r"
# define CMD_BUILTIN 3
# define CMD_BINARY 2
# define TRUE 1
# define FALSE 0

# define CWD_NAME_MAX_LENGTH 4096

// error of define here should move something !
// maybe allocate number of function later ?? who knows !
# define NB_BUILTINS_HERE 7
# define NB_MAX_HERE_DOC 16

typedef struct s_minishell
{
	int			should_exit;
	int			print_error;
	int			is_error_syntax;
	t_ast		*head_ast;
	int			fd_tty_in;
	int			fd_tty_out;
	int			fd_tty_err;
	int			last_child_id;
	int			last_error_code;
	int			previous_side;
	int			previous_type;
	int			first_cmd;
	int			nb_child_to_wait;
	int			fd1[2];
	int			fd2[2];
	t_list		*env;
	char		*builtins_name[NB_BUILTINS_HERE + 1];
	int			(*builtins_func[NB_BUILTINS_HERE])(t_vector args,\
											struct s_minishell *p_mini);
	int			fds_here_doc[NB_MAX_HERE_DOC];
	char		*cwd_name;
}			t_minishell;

typedef struct s_env
{
	char	*key;
	char	*value;
}			t_env;

# define ERROR_MALLOC -3

enum e_error_cod
{
	ERROR_READ = -1,
	ERROR_CLOSE = -2,
	ERROR_WRITE = -4,
	ERROR_DUP = -6,
	ERROR_PIPE = 4,
	ERROR_HERE_DOC_FILENAME,
	ERROR_UNLINK,
	ERROR_OPEN,
	ERROR_DUP2,
	ERROR_FORK,
	ERROR_UNCLOSED_S_QUOTES,
	ERROR_UNCLOSED_D_QUOTES,
	ERROR_UNMATCHING_PARENTHESIS,
	ERROR_EMPTY_PARENTHESIS,
	ERROR_FILENAME,
	ERROR_AROUND_OPENING_PARENTHESIS,
	ERROR_AROUND_CLOSING_PARENTHESIS,
	ERROR_AROUND_AND,
	ERROR_AROUND_OR,
	ERROR_AROUND_PIPE,
	ERROR_AROUND_SEQUENCE,
	ERROR_AROUND_REDIR_OUT,
	ERROR_AROUND_REDIR_IN,
	ERROR_AROUND_REDIR_HEREDOC,
	ERROR_AROUND_REDIR_APPEND,
	ERROR_UNKNOWN,
};
#endif
