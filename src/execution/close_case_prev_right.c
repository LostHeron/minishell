/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_case_prev_right.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:23:50 by jweber            #+#    #+#             */
/*   Updated: 2025/07/21 11:24:00 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

int	close_case_prev_right(t_minishell *p_mini, int final_ret)
{
	if (close(p_mini->fd1[0]) == -1)
	{
		perror("fn: close_case_prev_right: close(p_mini->fd1[0])");
		if (final_ret == 0)
			final_ret = ERROR_CLOSE;
	}
	p_mini->fd1[0] = -1;
	if (close(p_mini->fd1[1]) == -1)
	{
		perror("fn: close_case_prev_right: close(p_mini->fd1[1])");
		if (final_ret == 0)
			final_ret = ERROR_CLOSE;
	}
	p_mini->fd1[1] = -1;
	return (final_ret);
}
