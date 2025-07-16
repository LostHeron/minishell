/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sequence.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:40:37 by jweber            #+#    #+#             */
/*   Updated: 2025/07/15 11:05:25 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "minishell.h"
#include "execution.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int	exec_sequence(t_ast *ast, t_minishell *p_mini)
{
	int	ret;
	/*
	int	wait_id;
	int	child_ret;
	*/

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
	if (pipe(p_mini->fd2) == -1)
	{
		perror("exec_and.c : pipe(p_mini->fd2)");
		// return ??
	}
	ret = swap_fds(p_mini);
	if (ret != 0)
	{
		// do stuff ?
		return (ret);
	}
	ret = wait_children(p_mini);
	if (ret != 0)
	{
		// should exit program !
		// find a nice way !
	}
	/*
	if (p_mini->last_child_id != 0)
	{
		wait_id = wait(&child_ret);
		{
			while (wait_id != -1)
			{
				if (wait_id == p_mini->last_child_id)
					if (WIFEXITED(child_ret) != 0)
						p_mini->last_error_code = WEXITSTATUS(child_ret);
				wait_id = wait(&child_ret);
			}
		}
	}
	*/
	p_mini->previous_side = PREV_RIGHT;
	ret = exec_func(ast->arguments.op_args.right, p_mini);
	if (ret != 0)
	{
		// do stuff ?
		return (ret);
	}
	return (0);
}
