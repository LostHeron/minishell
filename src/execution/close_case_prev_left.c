/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_case_prev_left.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:21:08 by jweber            #+#    #+#             */
/*   Updated: 2025/07/21 11:21:51 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

static void	close_part1(t_minishell *p_mini, int *p_final_ret);
static void	close_part2(t_minishell *p_mini, int *p_final_ret);

int	close_case_prev_left(t_minishell *p_mini, int final_ret)
{
	close_part1(p_mini, &final_ret);
	close_part2(p_mini, &final_ret);
	return (final_ret);
}

static void	close_part1(t_minishell *p_mini, int *p_final_ret)
{
	if (close(p_mini->fd1[0]) == -1)
	{
		perror("fn: close_case_prev_left: close(p_mini->fd1[0])");
		if (*p_final_ret == 0)
			*p_final_ret = ERROR_CLOSE;
	}
	p_mini->fd1[0] = -1;
	if (close(p_mini->fd1[1]) == -1)
	{
		perror("fn: close_case_prev_left: close(p_mini->fd1[1])");
		if (*p_final_ret == 0)
			*p_final_ret = ERROR_CLOSE;
	}
	p_mini->fd1[1] = -1;
}

static void	close_part2(t_minishell *p_mini, int *p_final_ret)
{
	if (close(p_mini->fd2[0]) == -1)
	{
		perror("fn: close_case_prev_left: close(p_mini->fd2[0])");
		if (*p_final_ret == 0)
			*p_final_ret = ERROR_CLOSE;
	}
	p_mini->fd2[0] = -1;
	if (close(p_mini->fd2[1]) == -1)
	{
		perror("fn: close_case_prev_left: close(p_mini->fd2[1])");
		if (*p_final_ret == 0)
			*p_final_ret = ERROR_CLOSE;
	}
	p_mini->fd2[1] = -1;
}
