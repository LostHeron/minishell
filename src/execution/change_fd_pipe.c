/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_fd_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:04:18 by jweber            #+#    #+#             */
/*   Updated: 2025/07/21 11:29:07 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include <unistd.h>
#include <stdio.h>

static int	dup2_case_prev_left(t_minishell *p_mini);
static int	dup2_case_prev_right(t_minishell *p_mini);

int	change_fd_pipe(t_minishell *p_mini)
{
	int	final_ret;

	if (p_mini->previous_side == PREV_LEFT)
	{
		final_ret = dup2_case_prev_left(p_mini);
	}
	if (p_mini->previous_side == PREV_RIGHT)
	{
		final_ret = dup2_case_prev_right(p_mini);
	}
	if (p_mini->previous_side == PREV_RIGHT)
		return (close_case_prev_right(p_mini, final_ret));
	else
		return (close_case_prev_left(p_mini, final_ret));
}

static int	dup2_case_prev_left(t_minishell *p_mini)
{
	int	ret;

	if (p_mini->first_cmd != 1)
	{
		ret = dup2(p_mini->fd1[0], 0);
		if (ret == -1)
		{
			perror("dup2");
			return (ERROR_DUP2);
		}
	}
	if (dup2(p_mini->fd2[1], 1) == -1)
	{
		perror("dup2");
		return (ERROR_DUP2);
	}
	return (0);
}

static int	dup2_case_prev_right(t_minishell *p_mini)
{
	if (dup2(p_mini->fd1[0], 0) == -1)
	{
		perror("fn: dup2_case_prev_right: dup2(p_mini->fd1[0], 0)");
		return (ERROR_DUP2);
	}
	return (0);
}
