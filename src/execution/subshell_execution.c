/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 09:38:58 by jweber            #+#    #+#             */
/*   Updated: 2025/08/18 09:42:06 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft_init.h"
#include <minishell.h>
#include <stdio.h>

static int	setup_subshell(t_ast *ast, t_minishell *p_mini, int *p_final_ret);
static void	close_fd(int *p_fd, int *p_ret);

int	subshell_execution(t_ast *ast, t_minishell *p_mini)
{
	int	ret;
	int	final_ret;

	ret = setup_subshell(ast, p_mini, &final_ret);
	if (ret != 0)
		return (ret);
	ret = exec_func(ast->arguments.sub_args.sub, p_mini);
	if (ret != 0)
		final_ret = ret;
	close_fd(&(p_mini->fd1[1]), &final_ret);
	wait_children(p_mini, p_mini->nb_child_to_wait);
	close_fd(&(p_mini->fd1[0]), &final_ret);
	ret = close_saved_tty(p_mini);
	return (final_ret);
}

/*		This function, will set where a subshell as to write to, read from,
 *	and also closes every fd of pipe before opening new one
*/
static int	setup_subshell(t_ast *ast, t_minishell *p_mini, int *p_final_ret)
{
	int	ret;

	p_mini->last_child_id = 0;
	*p_final_ret = 0;
	ret = close_saved_tty(p_mini);
	if (ret != 0)
		return (ret);
	ret = make_redirections(ast->arguments.sub_args.dir_args, p_mini);
	if (ret != 0)
		return (ret);
	ret = init_saved_tty(p_mini);
	if (ret != 0)
		return (ret);
	p_mini->previous_side = PREV_NONE;
	p_mini->previous_type = -1;
	if (pipe(p_mini->fd1) == -1)
	{
		perror("pipe");
		free_tree(&p_mini->head_ast);
		return (ERROR_PIPE);
	}
	p_mini->first_cmd = 1;
	return (0);
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
