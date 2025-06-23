/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_or.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:54:30 by jweber            #+#    #+#             */
/*   Updated: 2025/06/23 12:56:25 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "minishell.h"
#include "execution.h"
#include <stdlib.h>
#include <sys/wait.h>

int	exec_or(t_ast *ast, t_minishell *p_mini)
{
	int	ret;
	int	wait_id;
	int	child_ret;

	p_mini->previous_type = AND;
	p_mini->previous_side = PREV_LEFT;
	ret = exec_func(ast->arguments.op_args.left, p_mini);
	if (ret != 0)
	{
		// do stuff ?
		return (ret);
	}
	// here should wait,
	// then retreive last command exit status
	// call next only if last error code is 0
	wait_id = wait(&child_ret);
	{
		if (wait_id == p_mini->last_child_id)
			if (WIFEXITED(child_ret) != 0)
				child_ret = WEXITSTATUS(child_ret);
	}
	if (child_ret != 0)
	{
		p_mini->previous_side = PREV_RIGHT;
		ret = exec_func(ast->arguments.op_args.right, p_mini);
		if (ret != 0)
		{
			// do stuff ?
			return (ret);
		}
	}
	return (0);
}
