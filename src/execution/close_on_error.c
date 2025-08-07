/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_on_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:49:51 by jweber            #+#    #+#             */
/*   Updated: 2025/07/21 14:55:58 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include <stdio.h>
#include <unistd.h>

static void	close_fd(int *p_fd);

void	close_on_error(t_minishell *p_mini)
{
	close_fd(&(p_mini->fd1[0]));
	close_fd(&(p_mini->fd1[1]));
	close_fd(&(p_mini->fd2[0]));
	close_fd(&(p_mini->fd2[1]));
	close_here_doc_fds(p_mini);
	return ;
}

static void	close_fd(int *p_fd)
{
	if (*p_fd > 0)
	{
		if (close(*p_fd) < 0)
			perror("fn: close_on_error: close");
		*p_fd = -1;
	}
}
