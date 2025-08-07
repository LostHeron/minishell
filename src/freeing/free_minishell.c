/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:47:21 by jweber            #+#    #+#             */
/*   Updated: 2025/07/02 15:42:21 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "freeing.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	close_fd(int *p_fd, int *p_final_ret);

int	free_minishell(t_minishell *p_mini)
{
	int	final_ret;

	final_ret = 0;
	close_fd(&p_mini->fd_tty_in, &final_ret);
	close_fd(&p_mini->fd_tty_out, &final_ret);
	close_fd(&p_mini->fd_tty_err, &final_ret);
	free_env(p_mini->env);
	free(p_mini->cwd_name);
	return (final_ret);
}

static void	close_fd(int *p_fd, int *p_final_ret)
{
	if (*p_fd > 0)
	{
		if (close(*p_fd) < 0)
		{
			perror("close\n");
			*p_final_ret = ERROR_CLOSE;
		}
		*p_fd = -1;
	}
	return ;
}
