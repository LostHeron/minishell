/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:08:14 by jweber            #+#    #+#             */
/*   Updated: 2025/07/15 15:55:52 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "ast.h"
#include "ft_memory.h"
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

static void	background_execution(t_ast *ast, t_minishell *p_mini);

int	exec_background(t_ast *ast, t_minishell *p_mini)
{
	int					pid;
	struct sigaction	sig_def;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (ERROR_FORK);
	}
	if (pid == 0)
	{
		ft_bzero(&sig_def, sizeof(sig_def));
		sig_def.sa_handler = SIG_DFL;
		sigaction(SIGQUIT, &sig_def, NULL);
		sigaction(SIGINT, &sig_def, NULL);
		background_execution(ast, p_mini);
	}
	else
	{
		p_mini->last_child_id = 0;
		p_mini->previous_side = PREV_RIGHT;
		if (ast->arguments.op_args.right->type != END_LINE)
			return (exec_func(ast->arguments.op_args.right, p_mini));
	}
	return (0);
}

/* This function should handle processes that are executed in background
 * it should wait for them to finish then 
*/
static void	background_execution(t_ast *ast, t_minishell *p_mini)
{
	int	ret;

	p_mini->previous_side = PREV_LEFT;
	ret = exec_func(ast->arguments.op_args.left, p_mini);
	close_fd1(p_mini);
	if (close(p_mini->fd_tty_copy) < 0)
		perror("close");
	wait_children(p_mini);
	if (ret != 0)
	{
		// really usefull ? lets see how does exec_func
		// can fail ;
		exit (ret);
	}
	exit(exit_child(p_mini, p_mini->last_error_code));
}
