/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:20:13 by jweber            #+#    #+#             */
/*   Updated: 2025/07/21 14:44:42 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

static void	get_child_return_value(t_minishell *p_mini, \
									int child_ret, int *p_ret);

int	wait_children(t_minishell *p_mini)
{
	int	child_ret;
	int	ret;
	int	wait_id;

	if (p_mini->last_child_id != 0)
	{
		wait_id = wait(&child_ret);
		while (wait_id != -1)
		{
			if (wait_id == p_mini->last_child_id)
			{
				get_child_return_value(p_mini, child_ret, &ret);
			}
			wait_id = wait(&child_ret);
		}
		return (ret);
	}
	else
		return (0);
}

static void	get_child_return_value(t_minishell *p_mini, \
									int child_ret, int *p_ret)
{
	if (WIFEXITED(child_ret) != 0)
	{
		p_mini->last_error_code = WEXITSTATUS(child_ret);
		*p_ret = 0;
	}
	else if (WIFSIGNALED(child_ret) != 0)
	{
		p_mini->last_error_code = WTERMSIG(child_ret);
		p_mini->last_error_code += 128;
		*p_ret = 0;
	}
	else
		*p_ret = 1;
	return ;
}
