/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:39:55 by jweber            #+#    #+#             */
/*   Updated: 2025/06/16 17:19:32 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_vectors.h"
# include "ft_lists_single.h"
# define WHITE_SPACES " \t\n\v\f\r"
# define CMD_BUILTIN 3
# define CMD_BINARY 2

# define PATH_NAME_MAX_LENGTH 4096

// error of define here should move something !
// maybe allocate number of function later ?? who knows !
#define NB_BUILTINS_HERE 7

typedef struct s_minishell
{
	int			fd_stdin;
	int			fd_stdout;
	int			fd_stderr;
	int			previous_side;
	int			previous_type;
	int			first_cmd;
	int			fd1[2];
	int			fd2[2];
	t_list		*env;
	t_vector	path;
	char		*builtins_name[NB_BUILTINS_HERE + 1];
	int			(*builtins_func[NB_BUILTINS_HERE])(t_vector args, \
											struct s_minishell *p_mini);
	char		*path_name;
	size_t		path_name_size;
}			t_minishell;

typedef struct s_env
{
	char	*key;
	char	*value;
}			t_env;

# define ERROR_MALLOC -3
# define ERROR_UNCLOSED_S_QUOTES -10
# define ERROR_UNCLOSED_D_QUOTES -11
# define ERROR_UNCLOSED_PARENTHESIS -12

#endif
