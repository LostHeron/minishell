/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 10:54:14 by jweber            #+#    #+#             */
/*   Updated: 2025/08/14 10:54:50 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"
#include "execution.h"
#include <stdio.h>

static void	close_fd(int *p_fd, int *p_ret);

/* to check :
 *	-> pipe fail : DONE -> OK !
 *	-> exec_func fail : DONE -> OK !
 *	-> first close_fd fail : DONE -> OK !
 *	-> second close_fd fail : DONE -> OK !
*/
int	run_exec(t_minishell *p_mini, t_ast **p_ast)
{
	int	ret_exec;
	int	ret;
	int	final_ret;

	final_ret = 0;
	p_mini->previous_side = PREV_NONE;
	p_mini->previous_type = -1;
	ret = pipe(p_mini->fd1);
	if (ret == -1)
	{
		perror("pipe");
		free_tree(p_ast);
		return (ERROR_PIPE);
	}
	p_mini->first_cmd = 1;
	ret_exec = exec_func(*p_ast, p_mini);
	if (ret_exec != 0)
		final_ret = ret_exec;
	close_fd(&(p_mini->fd1[1]), &final_ret);
	wait_children(p_mini, p_mini->nb_child_to_wait);
	close_fd(&(p_mini->fd1[0]), &final_ret);
	free_tree(p_ast);
	return (final_ret);
}

static void	close_fd(int *p_fd, int *p_ret)
{
	int	close_ret;

	if (*p_fd > 0)
	{
		close_ret = close(*p_fd);
		if (close_ret < 0)
		{
			perror("close");
			if (*p_ret == 0)
				*p_ret = ERROR_CLOSE;
		}
	}
}
