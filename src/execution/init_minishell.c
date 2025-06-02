/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:23:44 by jweber            #+#    #+#             */
/*   Updated: 2025/06/02 17:36:49 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

int	init_minishell(t_minishell *p_mini, char **env)
{
	p_mini->fd_stdin = dup(STDIN_FILENO);
	if (p_mini->fd_stdin == -1)
		perror(NULL);
	p_mini->fd_stdout = dup(STDOUT_FILENO);
	if (p_mini->fd_stdout == -1)
		perror(NULL);
	p_mini->fd_stderr = dup(STDERR_FILENO);
	if (p_mini->fd_stderr == -1)
		perror(NULL);
	if (init_env(p_mini, env) != 0)
	{
		// do stuff;
	}
	return (0);
}
