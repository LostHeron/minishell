/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:14:56 by jweber            #+#    #+#             */
/*   Updated: 2025/07/21 15:21:18 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "expand.h"
#include "minishell.h"
#include "ast.h"
#include "execution.h"
#include <unistd.h>
#include <stdio.h>

static int	subshell_execution(t_ast *ast, t_minishell *p_mini);

/*	This function should set up, then fork, then execute subshell
 * 	In case of success :
 *		...
 *	In case of failure : 
 *		...
*/
int	exec_subshell(t_ast *ast, t_minishell *p_mini)
{
	int	pid;
	int	ret;
	int	ret_exec;

	ret = expand_redir(&ast->arguments.sub_args.dir_args, *p_mini);
	if (ret != 0)
		return (ret);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (ERROR_FORK);
	}
	if (pid == 0)
	{
		p_mini->last_child_id = 0;
		ret_exec = subshell_execution(ast, p_mini);
		if (ret_exec != 0)
			exit(exit_child(p_mini, ret));
		else
			exit(exit_child(p_mini, p_mini->last_error_code));
	}
	else
	{
		p_mini->last_child_id = pid;
		p_mini->nb_child_to_wait++;
	}
	return (0);
}

static int	subshell_execution(t_ast *ast, t_minishell *p_mini)
{
	int	ret;

	ret = make_redirections(ast->arguments.sub_args.dir_args, p_mini);
	if (ret != 0)
	{
		return (ret);
	}
	p_mini->previous_side = PREV_NONE;
	p_mini->previous_type = -1;
	if (pipe(p_mini->fd1) == -1)
	{
		perror("fn : run_exec : pipe(p_mini->fd1)");
		free_tree(&p_mini->head_ast);
		return (ERROR_PIPE);
	}
	p_mini->first_cmd = 1;
	ret = exec_func(ast->arguments.sub_args.sub, p_mini);
	if (ret != 0)
		return (ret);
	close_fd1(p_mini);
	wait_children(p_mini);
	if (close(p_mini->fd_tty_copy) < 0)
		perror(\
	"in exec_subshell : close(p_mini->fd_stdin) at start of children\n");
	return (0);
}
