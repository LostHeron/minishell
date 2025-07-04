/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:02:33 by jweber            #+#    #+#             */
/*   Updated: 2025/07/04 18:38:40 by jweber           ###   ########.fr       */
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

static void	change_fd_pipe(t_minishell *p_mini);

int	child_execution(t_ast *ast, t_minishell *p_mini, int cmd_type)
{
	char		*cmd;
	int			ret;
	t_vector	path;

	if (close(p_mini->fd_tty_copy) < 0)
		perror("close(p_mini->fd_stdin) at start of children\n");
	if (p_mini->previous_type == PIPE)
		change_fd_pipe(p_mini);
	else
	{
		if (close(p_mini->fd1[0]) == -1)
			perror("child left : close(p_mini->fd1[0]");
		if (close(p_mini->fd1[1]) == -1)
			perror("child left : close(p_mini->fd1[1]");
	}
	ret = change_fd_redir(p_mini, ast);
	if (ret != 0)
	{
		// do stuff ?
		// return ? 
		// should close all fds !
		//exit(1);
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
			ret = get_path(p_mini, &path);
			if (ret != 0)
			{
				// do stuff !
				//return (ret);
				ft_vector_free(&path);
				exit(ret);
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
					exit(127);
				}
			}
		}
		execve(cmd, ast->arguments.com_args.content.data, NULL);
		if (errno == EACCES)
			exit(126);
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
			if (dup2(p_mini->fd1[0], 0) == -1)
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
