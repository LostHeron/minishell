/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:39:55 by jweber            #+#    #+#             */
/*   Updated: 2025/07/02 15:37:29 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_vectors.h"
# include "ft_lists_single.h"
# define WHITE_SPACES " \t\n\v\f\r"
# define CMD_BUILTIN 3
# define CMD_BINARY 2
# define TRUE 1
# define FALSE 0

# define CWD_NAME_MAX_LENGTH 4095

// error of define here should move something !
// maybe allocate number of function later ?? who knows !
#define NB_BUILTINS_HERE 7
#define NB_MAX_HERE_DOC 16

typedef struct s_minishell
{
	int			should_exit;
	int			fd_tty_copy;
	int			last_child_id;
	int			last_error_code;
	int			previous_side;
	int			previous_type;
	int			first_cmd;
	int			fd1[2];
	int			fd2[2];
	t_list		*env;
	char		*builtins_name[NB_BUILTINS_HERE + 1];
	int			(*builtins_func[NB_BUILTINS_HERE])(t_vector args, \
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
# define ERROR_WRITE -4
# define ERROR_READ -5
# define ERROR_DUP -6
# define ERROR_UNCLOSED_S_QUOTES 10
# define ERROR_UNCLOSED_D_QUOTES 11
# define ERROR_UNMATCHING_PARENTHESIS 12
# define ERROR_EMPTY_PARENTHESIS 13
# define ERROR_FILENAME 14

#endif
