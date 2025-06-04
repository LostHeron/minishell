/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:14:11 by jweber            #+#    #+#             */
/*   Updated: 2025/06/04 13:56:28 by jweber           ###   ########.fr       */
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

int	child_execution(t_ast *ast, t_minishell *p_mini)
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
	/*
	size_t	i;
	int		fd;

	i = 0;
	while (i < ast->arguments.com_args.dir_args.size)
	{
		if (((t_dirargs *)ast->arguments.com_args.dir_args.data)[i].dir == IN)
		{
			fd = open(\
		((t_dirargs *)ast->arguments.com_args.dir_args.data)[i].filename, \
		O_RDONLY \
			);
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
	*/
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

static void	change_fd_pipe(t_minishell *p_mini)
{
	if (p_mini->previous_side == PREV_LEFT)
		if (dup2(p_mini->fd[1], 1) == -1)
			; // do stuff ?
	if (p_mini->previous_side == PREV_RIGHT)
		if (dup2(p_mini->fd[0], 0) == -1)
			; // do stuff ?
	if (close(p_mini->fd[1]) == -1)
		perror(NULL);
	if (close(p_mini->fd[0]) == -1)
		perror(NULL);
}

