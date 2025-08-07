/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_saved_tty.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:37:28 by jweber            #+#    #+#             */
/*   Updated: 2025/07/30 12:42:02 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "freeing.h"
#include <stdio.h>
#include <unistd.h>

static int	init_in(t_minishell *p_mini);
static int	init_out(t_minishell *p_mini);
static int	init_err(t_minishell *p_mini);

int	init_saved_tty(t_minishell *p_mini)
{
	int	ret;

	ret = init_in(p_mini);
	if (ret != 0)
		return (ret);
	ret = init_out(p_mini);
	if (ret != 0)
		return (ret);
	ret = init_err(p_mini);
	if (ret != 0)
		return (ret);
	return (0);
}

static int	init_in(t_minishell *p_mini)
{
	p_mini->fd_tty_in = dup(STDIN_FILENO);
	if (p_mini->fd_tty_in < 0)
	{
		perror("dup");
		free_env(p_mini->env);
		free(p_mini->cwd_name);
		return (ERROR_DUP);
	}
	return (0);
}

static int	init_out(t_minishell *p_mini)
{
	p_mini->fd_tty_out = dup(STDOUT_FILENO);
	if (p_mini->fd_tty_out < 0)
	{
		perror("dup");
		if (p_mini->fd_tty_in > 0)
		{
			if (close(p_mini->fd_tty_in) < 0)
				perror("close");
			p_mini->fd_tty_in = -1;
		}
		free_env(p_mini->env);
		free(p_mini->cwd_name);
		return (ERROR_DUP);
	}
	return (0);
}

static int	init_err(t_minishell *p_mini)
{
	p_mini->fd_tty_err = dup(STDERR_FILENO);
	if (p_mini->fd_tty_out < 0)
	{
		perror("dup");
		if (p_mini->fd_tty_in > 0)
		{
			if (close(p_mini->fd_tty_in) < 0)
				perror("close");
			p_mini->fd_tty_in = -1;
		}
		if (p_mini->fd_tty_out > 0)
		{
			if (close(p_mini->fd_tty_out) < 0)
				perror("close");
			p_mini->fd_tty_out = -1;
		}
		free_env(p_mini->env);
		free(p_mini->cwd_name);
		return (ERROR_DUP);
	}
	return (0);
}
