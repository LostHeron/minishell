/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:43:35 by jweber            #+#    #+#             */
/*   Updated: 2025/07/21 11:27:57 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include <unistd.h>
#include <stdio.h>

static void	close_on_error(t_minishell *p_mini);
static int	case_no_pipe(t_minishell *p_mini);

/*		This function is called by exec_func->exec_command->case_forking->\
 * ->child_execution->make_redirection
 *
 *		This function should perform redirection, starting with pipe redirection
 *	using the fd1 and fd2 opened pipe !
 *	the it should close those file descriptor after having them dup2, 
 *	the following fd should be then closed :
 *		- p_mini->fd_tty_copy;
 *		- p_mini->fd1[0];
 *		- p_mini->fd1[1];
 *		if it has been opened : 
 *			- p_mini->fd2[0];
 *			- p_mini->fd2[1];
 *		and all here_doc fds opened previously 
 *
 *		Then the function should perform < << > >> redirections
 *	and close the fd opened after each performed redirection.
*/
int	make_redirections(t_ast *ast, t_minishell *p_mini)
{
	int	ret;

	if (close(p_mini->fd_tty_copy) < 0)
	{
		perror("close(p_mini->fd_stdin) at start of children\n");
		close_on_error(p_mini);
		return (ERROR_CLOSE);
	}
	if (p_mini->previous_type == PIPE)
	{
		ret = change_fd_pipe(p_mini);
		if (ret != 0)
			return (ret);
	}
	else
	{
		ret = case_no_pipe(p_mini);
		if (ret != 0)
			return (ret);
	}
	ret = change_fd_redir(p_mini, ast->arguments.com_args.dir_args);
	return (ret);
}

static void	close_on_error(t_minishell *p_mini)
{
	if (p_mini->fd1[0] > 0)
		if (close(p_mini->fd1[0]) < 0)
			perror("fn: close_on_error: close(p_mini->fd1[0])");
	if (p_mini->fd1[1] > 0)
		if (close(p_mini->fd1[1]) < 0)
			perror("fn: close_on_error: close(p_mini->fd1[1])");
	if (p_mini->fd2[0] > 0)
		if (close(p_mini->fd2[0]) < 0)
			perror("fn: close_on_error: close(p_mini->fd2[0])");
	if (p_mini->fd2[1] > 0)
		if (close(p_mini->fd2[1]) < 0)
			perror("fn: close_on_error: close(p_mini->fd2[1])");
	close_here_doc_fds(p_mini);
	return ;
}

static int	case_no_pipe(t_minishell *p_mini)
{
	int	ret;

	ret = 0;
	if (close(p_mini->fd1[0]) == -1)
	{
		perror("fn: child_execution: child left: close(p_mini->fd1[0]");
		ret = ERROR_CLOSE;
	}
	if (close(p_mini->fd1[1]) == -1)
	{
		perror("fn: child_execution: child left: close(p_mini->fd1[1]");
		ret = ERROR_CLOSE;
	}
	return (ret);
}
