/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:13:46 by jweber            #+#    #+#             */
/*   Updated: 2025/06/02 16:15:02 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "ast.h"
# include "minishell.h"

enum	e_previous
{
	PREV_NONE,
	PREV_RIGHT,
	PREV_LEFT,
};

int		exec_command(t_ast *ast, t_minishell *p_mini);
int		init_minishell(t_minishell *p_mini, char **env);
int		init_env(t_minishell *p_mini, char **env);
int		init_path(t_minishell *p_mini);
int		find_command(char **p_cmd, t_vector path);
void	free_minishell(t_minishell *p_mini);

#endif
