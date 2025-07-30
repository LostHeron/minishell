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

int	free_minishell(t_minishell *p_mini)
{
	int	final_ret;

	final_ret = 0;
	if (close(p_mini->fd_tty_in) < 0)
	{
		perror("fn : free_minishell : close(p_mini->fd_tty_copy)\n");
		final_ret = ERROR_CLOSE;
	}
	if (close(p_mini->fd_tty_out) < 0)
	{
		perror("fn : free_minishell : close(p_mini->fd_tty_copy)\n");
		final_ret = ERROR_CLOSE;
	}
	if (close(p_mini->fd_tty_err) < 0)
	{
		perror("fn : free_minishell : close(p_mini->fd_tty_copy)\n");
		final_ret = ERROR_CLOSE;
	}
	free_env(p_mini->env);
	free(p_mini->cwd_name);
	return (final_ret);
}
