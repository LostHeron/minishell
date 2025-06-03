/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:23:44 by jweber            #+#    #+#             */
/*   Updated: 2025/06/03 16:32:07 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "printing.h"
#include <unistd.h>
#include <stdio.h>

int	init_minishell(t_minishell *p_mini, char **env)
{
	int	ret;

	p_mini->fd_stdin = dup(STDIN_FILENO);
	if (p_mini->fd_stdin == -1)
		perror(NULL);
	p_mini->fd_stdout = dup(STDOUT_FILENO);
	if (p_mini->fd_stdout == -1)
		perror(NULL);
	p_mini->fd_stderr = dup(STDERR_FILENO);
	if (p_mini->fd_stderr == -1)
		perror(NULL);
	ret = init_env(p_mini, env);
	if (ret != 0)
	{
		// do stuff;
		return (ret);
	}
	ret = init_path(p_mini);
	if (ret != 0)
	{
		// do stuff
		return (ret);
	}
	print_path(p_mini);
	return (0);
}
