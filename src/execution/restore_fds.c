/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_fds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:46:05 by jweber            #+#    #+#             */
/*   Updated: 2025/07/04 18:48:37 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

int	restore_fds(t_minishell *p_mini)
{
	if (dup2(p_mini->fd_tty_copy, 2) < 0)
	{
		perror("in restore_fd : dup2(p_mini->fd_stderr, 2)");
		return (ERROR_DUP2);
	}
	if (dup2(p_mini->fd_tty_copy, 1) < 0)
	{
		perror("in restore_fd : dup2(p_mini->fd_stderr, 2)");
		return (ERROR_DUP2);
	}
	if (dup2(p_mini->fd_tty_copy, 0) < 0)
	{
		perror("in restore_fd : dup2(p_mini->fd_stderr, 2)");
		return (ERROR_DUP2);
	}
	return (0);
}
