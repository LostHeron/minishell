/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:58:00 by jweber            #+#    #+#             */
/*   Updated: 2025/06/04 16:34:47 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "ast.h"
#include <unistd.h>
#include <stdio.h>

static int	swap_fds(t_minishell *p_mini);

int	exec_pipe(t_ast *ast, t_minishell *p_mini)
{
	int	ret;

	if (pipe(p_mini->fd2) == -1)
	{
		// do stuff
		// return?
		;
	}
	p_mini->previous_type = PIPE;
	p_mini->previous_side = PREV_LEFT;
	exec_func(ast->arguments.op_args.left, p_mini);
	p_mini->previous_side = PREV_RIGHT;
	ret = swap_fds(p_mini);
	if (ret != 0)
	{
		// do stuff ?
		// return  ?? 
	}
	exec_func(ast->arguments.op_args.right, p_mini);
	/*
	if (close(p_mini->fd2[0]) == -1)
		perror("close(p_mini->fd2[0])");
	if (close(p_mini->fd2[1]) == -1)
		perror("close(p_mini->fd2[1])");
	*/
	return (0);
}

static int	swap_fds(t_minishell *p_mini)
{
	if (close(p_mini->fd1[0]) != 0)
		perror("close(p_minit->fd1[0])");
	if (close(p_mini->fd1[1]) != 0)
		perror("close(p_minit->fd1[1])");
	p_mini->fd1[0] = p_mini->fd2[0];
	p_mini->fd1[1] = p_mini->fd2[1];
	return (0);
}
