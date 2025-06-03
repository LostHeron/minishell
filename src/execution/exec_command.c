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
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int	exec_command(t_ast *ast, t_minishell *p_mini)
{
	int	pid;
	int	ret;
	char	*cmd;
	/*
	int	fd_a[2];
	int	fd_b[2];
	if (ast->type == PIPE)
	{
		exec_command(ast->arguments.op_args.left);
	}
	*/
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
			if (((char **)ast->arguments.com_args.content.data)[0][0] == '/')
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
					return (1);
				}
			}
			execve(cmd, ast->arguments.com_args.content.data, NULL);
			perror(cmd);
		}
		else
		{
			wait(NULL);
		}
	}
	return (0);
}
