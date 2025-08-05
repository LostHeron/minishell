/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_or.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:54:30 by jweber            #+#    #+#             */
/*   Updated: 2025/07/15 10:40:45 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "minishell.h"
#include "execution.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

static int	return_error_pipe(void);

int	exec_or(t_ast *ast, t_minishell *p_mini)
{
	int	ret;

	p_mini->previous_type = AND;
	p_mini->previous_side = PREV_LEFT;
	ret = exec_func(ast->arguments.op_args.left, p_mini);
	if (ret != 0)
		return (ret);
	if (pipe(p_mini->fd2) == -1)
		return (return_error_pipe());
	ret = swap_fds(p_mini);
	if (ret != 0)
		return (ret);
	ret = wait_children(p_mini, p_mini->nb_child_to_wait);
	if (ret != 0)
		return (ret);
	if (p_mini->last_error_code != 0)
	{
		p_mini->previous_side = PREV_RIGHT;
		ret = exec_func(ast->arguments.op_args.right, p_mini);
		if (ret != 0)
			return (ret);
	}
	return (0);
}

static int	return_error_pipe(void)
{
	perror("pipe");
	return (ERROR_PIPE);
}
