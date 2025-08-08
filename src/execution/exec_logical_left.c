/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_logical_left.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:04:57 by jweber            #+#    #+#             */
/*   Updated: 2025/08/08 14:22:46 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include <stdio.h>
#include <unistd.h>

int	exec_logical_left(t_ast *ast, t_minishell *p_mini)
{
	int	ret;

	p_mini->previous_side = PREV_LEFT;
	ret = exec_func(ast->arguments.op_args.left, p_mini);
	if (ret != 0)
		return (ret);
	if (pipe(p_mini->fd2) == -1)
	{
		perror("pipe");
		return (ERROR_PIPE);
	}
	ret = swap_fds(p_mini);
	if (ret != 0)
		return (ret);
	ret = wait_children(p_mini, p_mini->nb_child_to_wait);
	return (ret);
}
