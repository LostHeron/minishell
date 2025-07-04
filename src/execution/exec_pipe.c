/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:58:00 by jweber            #+#    #+#             */
/*   Updated: 2025/06/23 17:26:57 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "ast.h"
#include <unistd.h>

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
	ret = exec_func(ast->arguments.op_args.left, p_mini);
	if (ret != 0)
	{
		// do stuff ?
		return (ret);
	}
	p_mini->previous_side = PREV_RIGHT;
	ret = swap_fds(p_mini);
	if (ret != 0)
	{
		// do stuff ?
		// return  ?? 
	}
	ret = exec_func(ast->arguments.op_args.right, p_mini);
	if (ret != 0)
	{
		// do stuff ?
		return (ret);
	}
	return (0);
}
