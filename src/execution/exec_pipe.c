/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:58:00 by jweber            #+#    #+#             */
/*   Updated: 2025/07/15 13:43:12 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "ast.h"
#include <unistd.h>
#include <stdio.h>

static int	launch_left(t_ast *ast, t_minishell *p_mini);
static int	launch_right(t_ast *ast, t_minishell *p_mini);

int	exec_pipe(t_ast *ast, t_minishell *p_mini)
{
	int	ret;

	p_mini->previous_type = PIPE;
	ret = launch_left(ast, p_mini);
	if (ret != 0)
		return (ret);
	ret = swap_fds(p_mini);
	if (ret != 0)
	{
		if (close(p_mini->fd2[0]) < 0)
			perror("close");
		if (close(p_mini->fd2[1]) < 0)
			perror("close");
		return (ret);
	}
	ret = launch_right(ast, p_mini);
	if (ret != 0)
		return (ret);
	/*
	p_mini->previous_side = PREV_RIGHT;
	ret = exec_func(ast->arguments.op_args.right, p_mini);
	if (ret != 0 || p_mini->is_main_process == FALSE)
	{
		// do stuff ?
		if (close(p_mini->fd2[0]) < 0)
			perror("close");
		if (close(p_mini->fd2[1]) < 0)
			perror("close");
		return (ret);
	}
	*/
	return (0);
}

static int	launch_left(t_ast *ast, t_minishell *p_mini)
{
	int	ret;

	if (pipe(p_mini->fd2) == -1)
	{
		perror("fn: exec_pipe: pipe");
		return (ERROR_PIPE);
	}
	p_mini->previous_side = PREV_LEFT;
	ret = exec_func(ast->arguments.op_args.left, p_mini);
	if (ret != 0)
	{
		if (close(p_mini->fd2[0]) < 0)
			perror("close");
		if (close(p_mini->fd2[1]) < 0)
			perror("close");
		return (ret);
	}
	return (0);
}

static int	launch_right(t_ast *ast, t_minishell *p_mini)
{
	int	ret;

	p_mini->previous_side = PREV_RIGHT;
	ret = exec_func(ast->arguments.op_args.right, p_mini);
	if (ret != 0)
	{
		if (close(p_mini->fd2[0]) < 0)
			perror("close");
		if (close(p_mini->fd2[1]) < 0)
			perror("close");
		return (ret);
	}
	return (0);
}
