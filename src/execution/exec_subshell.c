/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:14:56 by jweber            #+#    #+#             */
/*   Updated: 2025/08/18 10:38:21 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "expand.h"
#include "minishell.h"
#include "ast.h"
#include "execution.h"
#include "printing.h"
#include <unistd.h>
#include <stdio.h>

static int	expand_redir_fail(t_minishell *p_mini, int ret);
static void	print_error_exit(t_minishell *p_mini, int ret_exec);
static void	parent_subshell(t_minishell *p_mini, int pid);

/* This function should set up, then fork, then execute subshell
 * to check:
 *	-> expand_redir fail : DONE -> OK !
 *	-> fork fail : DONE -> OK !
 *	-> subshell_execution fail : DONE -> OK !
*/
int	exec_subshell(t_ast *ast, t_minishell *p_mini)
{
	int	pid;
	int	ret;
	int	ret_exec;

	ret = expand_redir(&ast->arguments.sub_args.dir_args, *p_mini);
	if (ret != 0)
		return (expand_redir_fail(p_mini, ret));
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (ERROR_FORK);
	}
	if (pid == 0)
	{
		ret_exec = subshell_execution(ast, p_mini);
		if (ret_exec != 0)
			print_error_exit(p_mini, ret_exec);
		else
			exit(exit_child(p_mini, p_mini->last_error_code));
	}
	else
		parent_subshell(p_mini, pid);
	return (0);
}

static int	expand_redir_fail(t_minishell *p_mini, int ret)
{
	if (ret > 0)
		p_mini->last_error_code = 1;
	else
		p_mini->last_error_code = 2;
	return (ret);
}

static void	print_error_exit(t_minishell *p_mini, int err_code)
{
	print_error(err_code);
	if (err_code == ERROR_OPEN || err_code == ERROR_FILENAME)
		exit(exit_child(p_mini, 1));
	else
		exit(exit_child(p_mini, 2));
}

static void	parent_subshell(t_minishell *p_mini, int pid)
{
	p_mini->last_child_id = pid;
	p_mini->nb_child_to_wait++;
}
