/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_fds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:46:05 by jweber            #+#    #+#             */
/*   Updated: 2025/07/30 13:02:28 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

int	restore_fds(t_minishell *p_mini)
{
	int	ret;

	ret = 0;
	if (dup2(p_mini->fd_tty_err, STDERR_FILENO) < 0)
	{
		perror("dup2");
		ret = ERROR_DUP2;
	}
	if (dup2(p_mini->fd_tty_in, STDIN_FILENO) < 0)
	{
		perror("dup2");
		ret = ERROR_DUP2;
	}
	if (dup2(p_mini->fd_tty_out, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		ret = ERROR_DUP2;
	}
	return (ret);
}
