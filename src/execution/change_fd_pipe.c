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

/* to check
 *	-> dup2_case_prev_left fail : DONE -> OK !
 *	-> dup2_case_prev_right fail : DONE -> OK !
 *	-> close_case_pipe fail : DONE -> OK !
*/
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
	return (close_case_pipe(p_mini, final_ret));
}

/* to check
 *	-> first dup2 fail : DONE -> OK !
 *	-> second dup2 fail : DONE -> OK !
*/
static int	dup2_case_prev_left(t_minishell *p_mini)
{
	int	ret;

	if (p_mini->first_cmd != 1)
	{
		ret = dup2(p_mini->fd1[0], STDIN_FILENO);
		if (ret < 0)
		{
			perror("dup2");
			return (ERROR_DUP2);
		}
	}
	ret = dup2(p_mini->fd2[1], STDOUT_FILENO);
	if (ret < 0)
	{
		perror("dup2");
		return (ERROR_DUP2);
	}
	return (0);
}

/* to check 
 *	-> dup2 fail : DONE -> OK !
*/
static int	dup2_case_prev_right(t_minishell *p_mini)
{
	int	ret;

	ret = dup2(p_mini->fd1[0], STDIN_FILENO);
	if (ret < 0)
	{
		perror("dup2");
		return (ERROR_DUP2);
	}
	return (0);
}
