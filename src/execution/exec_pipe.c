/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:58:00 by jweber            #+#    #+#             */
/*   Updated: 2025/06/04 12:59:48 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "ast.h"
#include <unistd.h>
#include <stdio.h>

int	exec_pipe(t_ast *ast, t_minishell *p_mini)
{
	if (pipe(p_mini->fd) == -1)
	{
		// do stuff
		// return?
		;
	}
	p_mini->previous_type = PIPE;
	p_mini->previous_side = PREV_LEFT;
	exec_func(ast->arguments.op_args.left, p_mini);
	p_mini->previous_side = PREV_RIGHT;
	exec_func(ast->arguments.op_args.right, p_mini);
	if (close(p_mini->fd[0]) == -1)
		perror(NULL);
	if (close(p_mini->fd[1]) == -1)
		perror(NULL);
	return (0);
}
