/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:12:52 by jweber            #+#    #+#             */
/*   Updated: 2025/06/03 14:05:11 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "execution.h"
#include "minishell.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int	exec_command(t_ast *ast, t_minishell *p_mini)
{
	int		pid;
	int		ret;
	char	*cmd;
	size_t	i;
	int		fd;

	if (ast->type == PIPE)
	{
		if (pipe(p_mini->fd) == -1)
		{
			// do stuff
			// return?
			;
		}
		p_mini->previous_type = PIPE;
		p_mini->previous_side = PREV_LEFT;
		exec_command(ast->arguments.op_args.left, p_mini);
		p_mini->previous_side = PREV_RIGHT;
		exec_command(ast->arguments.op_args.right, p_mini);
		if (close(p_mini->fd[0]) == -1)
			perror(NULL);
		if (close(p_mini->fd[1]) == -1)
			perror(NULL);
	}
	if (ast->type == COMMAND)
	{
		pid = fork();
		if (pid == -1)
		{
			// see later !
			;
		}
		if (pid == 0)
		{
			i = 0;
			if (p_mini->previous_type == PIPE)
			{
				if (p_mini->previous_side == PREV_LEFT)
					dup2(p_mini->fd[1], 1);
				if (p_mini->previous_side == PREV_RIGHT)
					dup2(p_mini->fd[0], 0);
				if (close(p_mini->fd[1]) == -1)
					perror(NULL);
				if (close(p_mini->fd[0]) == -1)
					perror(NULL);
			}
			while (i < ast->arguments.com_args.dir_args.size)
			{
				if (((t_dirargs *)ast->arguments.com_args.dir_args.data)[i].dir == IN)
				{
					fd = open(((t_dirargs *)ast->arguments.com_args.dir_args.data)[i].filename, O_RDONLY);
					if (fd == -1)
					{
						// do stuff !
					}
					if (dup2(fd, 0) == -1)
					{
						// do stuff !
					}
					close(fd);
				}
				else if (((t_dirargs *)ast->arguments.com_args.dir_args.data)[i].dir == OUT)
				{
					fd = open(((t_dirargs *)ast->arguments.com_args.dir_args.data)[i].filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
					if (fd == -1)
					{
						// do stuff !
					}
					if (dup2(fd, 1) == -1)
					{
						// do stuff !
					}
					close(fd);
				}
				i++;
			}
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
					exit(127);
				}
			}
			execve(cmd, ast->arguments.com_args.content.data, NULL);
			perror(cmd);
			exit(errno);
		}
		else
		{
			;
		}
	}
	return (0);
}
