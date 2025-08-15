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

/* to check :
 *	-> pipe fail : DONE -> OK !
 *	-> exec_func fail : TO DO ;
 *	-> close_fd1 fail : TO DO ;
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
	wait_children(p_mini, p_mini->nb_child_to_wait - 1);
	ret = close_fd1(p_mini);
	if (ret != 0 && final_ret == 0)
		final_ret = ret;
	wait_children(p_mini, p_mini->nb_child_to_wait);
	free_tree(p_ast);
	return (final_ret);
}
