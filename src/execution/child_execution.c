/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:02:33 by jweber            #+#    #+#             */
/*   Updated: 2025/07/17 17:59:19 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include "minishell.h"
#include "ast.h"
#include "execution.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

/* at this point, we are already in the child process
 * of the command type node, 
 * we entered here from exec_command call !
*/
int	child_execution(t_ast *ast, t_minishell *p_mini, int cmd_type)
{
	char		*cmd;
	int			ret;
	t_vector	path;

	if (close(p_mini->fd_tty_copy) < 0)
		perror("close(p_mini->fd_stdin) at start of children\n");
	if (p_mini->previous_type == PIPE)
	{
		ret = change_fd_pipe(p_mini);
		if (ret != 0)
		{
			// do something
			return (ret);
		}
	}
	else
	{
		if (close(p_mini->fd1[0]) == -1)
			perror("fn: child_execution: child left: close(p_mini->fd1[0]");
		if (close(p_mini->fd1[1]) == -1)
			perror("fn: child_execution: child left: close(p_mini->fd1[1]");
	}
	ret = change_fd_redir(p_mini, ast);
	if (ret != 0)
	{
		// do stuff ?
		// return ? 
		// should close all fds !
		//no no exit !exit(1);
		//only return here 
	}
	if (cmd_type == CMD_BUILTIN)
	{
		ret = call_builtins(p_mini, ast->arguments.com_args.content);
		return (ret);
	}
	else
	{
		if (((char **)ast->arguments.com_args.content.data)[0][0] == '/' || \
		((char **)ast->arguments.com_args.content.data)[0][0] == '.')
		{
			cmd = ((char **)ast->arguments.com_args.content.data)[0];
		}
		else
		{
			ret = get_path(p_mini, &path);
			if (ret != 0)
			{
				// do stuff !
				//return (ret);
				// ft_vector_free(&path); should not do this, 
				// it is already freed in get_path
				return (ret);
			}
			ret = find_command(ast->arguments.com_args.content.data, path);
			cmd = ((char **)ast->arguments.com_args.content.data)[0];
			ft_vector_free(&path);
			if (ret != 0)
			{
				// do stuff ?
				//return (ret);
				if (ret < 0)
					exit(ret);
				else
				{
					printf("%s: command not found\n", cmd);
					// do some cleaning stuff or leaks !
					return(127);
				}
			}
		}
		execve(cmd, ast->arguments.com_args.content.data, NULL);
		perror(cmd);
		if (errno == EACCES)
			return (126);
		return (1);
	}
}
