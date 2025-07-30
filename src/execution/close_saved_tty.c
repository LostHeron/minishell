/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_saved_tty.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:51:13 by jweber            #+#    #+#             */
/*   Updated: 2025/07/30 13:00:05 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include <stdio.h>
#include <unistd.h>

int	close_saved_tty(t_minishell *p_mini)
{
	int	ret;
	int	final_ret;

	final_ret = 0;
	ret = close(p_mini->fd_tty_in);
	if (ret < 0)
	{
		perror("close");
		final_ret = ERROR_CLOSE;
	}
	ret = close(p_mini->fd_tty_out);
	if (ret < 0)
	{
		perror("close");
		final_ret = ERROR_CLOSE;
	}
	ret = close(p_mini->fd_tty_err);
	if (ret < 0)
	{
		perror("close");
		final_ret = ERROR_CLOSE;
	}
	return (final_ret);
}
