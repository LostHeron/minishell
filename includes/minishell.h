/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:39:55 by jweber            #+#    #+#             */
/*   Updated: 2025/06/02 17:41:15 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "ft_vectors.h"
# define WHITE_SPACES " \t\n\v\f\r"

# include "ft_lists_single.h"

typedef struct s_minishell
{
	int			fd_stdin;
	int			fd_stdout;
	int			fd_stderr;
	t_list		*env;
	t_vector	path;
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
