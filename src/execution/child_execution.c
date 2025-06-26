/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:02:33 by jweber            #+#    #+#             */
/*   Updated: 2025/06/26 13:52:22 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"
#include "execution.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

static void	change_fd_pipe(t_minishell *p_mini);

int	child_execution(t_ast *ast, t_minishell *p_mini, int cmd_type)
{
	char	*cmd;
	int		ret;

	if (p_mini->previous_type == PIPE)
		change_fd_pipe(p_mini);
	ret = change_fd_redir(ast);
	if (ret != 0)
	{
		// do stuff ?
		// return ? 
	}
	if (cmd_type == CMD_BUILTIN)
	{
		ret = call_builtins(p_mini, ast->arguments.com_args.content);
		exit (ret);
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
			ret = find_command(ast->arguments.com_args.content.data, p_mini->path);
			cmd = ((char **)ast->arguments.com_args.content.data)[0];
			if (ret != 0)
			{
				printf("%s: command not found\n", cmd);
				// do some cleaning stuff or leaks !
				exit(127);
			}
		}
		execve(cmd, ast->arguments.com_args.content.data, NULL);
		perror(cmd);
		exit(errno);
	}
}

static void	change_fd_pipe(t_minishell *p_mini)
{
	if (p_mini->previous_side == PREV_LEFT)
	{
		if (p_mini->first_cmd != 1)
		{
			if (dup2(p_mini->fd1[0], 0) == -1) // but must be executed only if not first cmd 
				perror(NULL); // do stuff ?
		}
		if (dup2(p_mini->fd2[1], 1) == -1)
			perror(NULL); // do stuff ?
	}
	if (p_mini->previous_side == PREV_RIGHT)
		if (dup2(p_mini->fd1[0], 0) == -1)
			; // do stuff ?
	if (p_mini->previous_side == PREV_RIGHT)
	{
		if (close(p_mini->fd1[0]) == -1)
			perror("child right : close(p_mini->fd1[0]");
		if (close(p_mini->fd1[1]) == -1)
			perror("child right : close(p_mini->fd1[1]");
	}
	else
	{
		if (close(p_mini->fd1[0]) == -1)
			perror("child left : close(p_mini->fd1[0]");
		if (close(p_mini->fd1[1]) == -1)
			perror("child left : close(p_mini->fd1[1]");
		if (close(p_mini->fd2[0]) == -1)
			perror("child right : close(p_mini->fd2[0]");
		if (close(p_mini->fd2[1]) == -1)
			perror("child right : close(p_mini->fd2[1]");
	}
}
