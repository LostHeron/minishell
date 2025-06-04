/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_fd_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:44:39 by jweber            #+#    #+#             */
/*   Updated: 2025/06/04 14:08:29 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

static int	redir_in(t_ast *ast, size_t	i);
static int	redir_out(t_ast *ast, size_t i);
static int	redir_append(t_ast *ast, size_t i);
/*
static int	redir_heredoc(t_ast *ast, size_t i);
*/

int	change_fd_redir(t_ast *ast)
{
	size_t	i;
	int		ret;

	i = 0;
	while (i < ast->arguments.com_args.dir_args.size)
	{
		if (((t_dirargs *)ast->arguments.com_args.dir_args.data)[i].dir == IN)
		{
			ret = redir_in(ast, i); 
			if (ret != 0)
			{
				// do stuff ?
				// return ? 
				// ;
			}
		}
		else if (((t_dirargs *)ast->arguments.com_args.dir_args.data)[i].dir == OUT)
		{
			ret = redir_out(ast, i); 
			if (ret != 0)
			{
				// do stuff ?
				// return ? 
				// ;
			}
		}
		else if (((t_dirargs *)ast->arguments.com_args.dir_args.data)[i].dir == APPEND)
		{
			ret = redir_append(ast, i); 
			if (ret != 0)
			{
				// do stuff ?
				// return ? 
				// ;
			}
		}
		i++;
	}
	return (0);
}

static int	redir_in(t_ast *ast, size_t	i)
{
	int		fd;

	fd = open(\
		((t_dirargs *)ast->arguments.com_args.dir_args.data)[i].filename, \
		O_RDONLY \
	);
	if (fd == -1)
	{
		// do stuff !
		// return ?
	}
	if (dup2(fd, 0) == -1)
	{
		// do stuff !
		// return ?
	}
	if (close(fd) == -1)
		perror("close(fd)");
	return (0);
}

static int	redir_out(t_ast *ast, size_t i)
{
	int	fd;

	fd = open(\
		((t_dirargs *)ast->arguments.com_args.dir_args.data)[i].filename, \
		O_WRONLY | O_CREAT | O_TRUNC, \
		0666 \
	);
	if (fd == -1)
	{
		// do stuff !
		// return ?
	}
	if (dup2(fd, 1) == -1)
	{
		// do stuff !
		// return ?
	}
	if (close(fd) == -1)
		perror("close(fd)");
	return (0);
}

static int	redir_append(t_ast *ast, size_t i)
{
	int	fd;

	fd = open(\
		((t_dirargs *)ast->arguments.com_args.dir_args.data)[i].filename, \
		O_WRONLY | O_CREAT | O_APPEND, \
		0666 \
	);
	if (fd == -1)
	{
		// do stuff !
		// return ?
	}
	if (dup2(fd, 1) == -1)
	{
		// do stuff !
		// return ?
	}
	if (close(fd) == -1)
		perror("close(fd)");
	return (0);
}
