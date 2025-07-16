/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_fd_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:04:18 by jweber            #+#    #+#             */
/*   Updated: 2025/07/15 16:05:07 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include <unistd.h>
#include <stdio.h>

void	change_fd_pipe(t_minishell *p_mini)
{
	if (p_mini->previous_side == PREV_LEFT)
	{
		if (p_mini->first_cmd != 1)
		{
			if (dup2(p_mini->fd1[0], 0) == -1)
				perror(NULL); // do something else
		}
		if (dup2(p_mini->fd2[1], 1) == -1)
			perror(NULL); // do something else
	}
	if (p_mini->previous_side == PREV_RIGHT)
		if (dup2(p_mini->fd1[0], 0) == -1)
			perror("dup2(p_mini->fd1[0], 0)");
	if (p_mini->previous_side == PREV_RIGHT)
	{
		if (close(p_mini->fd1[0]) == -1)
			perror("fn: change_fd_pipe: child right : close(p_mini->fd1[0]");
		if (close(p_mini->fd1[1]) == -1)
			perror("fn: change_fd_pipe: child right : close(p_mini->fd1[1]");
	}
	else
	{
		if (close(p_mini->fd1[0]) == -1)
			perror("fn: change_fd_pipe: child left : close(p_mini->fd1[0]");
		if (close(p_mini->fd1[1]) == -1)
			perror("fn: change_fd_pipe: child left : close(p_mini->fd1[1]");
		if (close(p_mini->fd2[0]) == -1)
			perror("fn: change_fd_pipe: child right : close(p_mini->fd2[0]");
		if (close(p_mini->fd2[1]) == -1)
			perror("fn: change_fd_pipe: child right : close(p_mini->fd2[1]");
	}
}
