/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_fd_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:44:39 by jweber            #+#    #+#             */
/*   Updated: 2025/07/04 19:11:38 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "minishell.h"
#include "execution.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

static void	init_redir_table(int (*redir_table[3])(t_ast *ast, size_t i));
static int	redir_in(t_ast *ast, size_t	i);
static int	redir_out(t_ast *ast, size_t i);
static int	redir_append(t_ast *ast, size_t i);
static int	redir_here_doc(t_minishell *p_mini, t_ast *ast, size_t i);
/*
static int	redir_heredoc(t_ast *ast, size_t i);
*/

int	change_fd_redir(t_minishell *p_mini, t_ast *ast)
{
	size_t	i;
	int		ret;
	int		(*redir_table[3])(t_ast *ast, size_t i);

	i = 0;
	init_redir_table(redir_table);
	while (i < ast->arguments.com_args.dir_args.size)
	{
		if (\
	IN <= ((t_dirargs *)ast->arguments.com_args.dir_args.data)[i].dir && \
	((t_dirargs *)ast->arguments.com_args.dir_args.data)[i].dir <= APPEND)
		{
			ret = redir_table[((t_dirargs *)ast->arguments.com_args.dir_args.data)[i].dir](ast, i);
			if (ret != 0)
				return (1);
		}
		else if (((t_dirargs *)ast->arguments.com_args.dir_args.data)[i].dir == HEREDOC)
		{
			ret = redir_here_doc(p_mini, ast, i);
			if (ret != 0)
				return (1);
		}
		i++;
	}
	ret = close_here_doc_fds(p_mini); // not sure about this function !
	if (ret != 0)
		return (1);
	return (0);
}

static void	init_redir_table(int (*redir_table[3])(t_ast *ast, size_t i))
{
	redir_table[IN] = &redir_in;
	redir_table[OUT] = &redir_out;
	redir_table[APPEND] = &redir_append;
}

static int	redir_in(t_ast *ast, size_t	i)
{
	int		fd;

	fd = open(\
		((t_dirargs *)ast->arguments.com_args.dir_args.data)[i].filename, \
		O_RDONLY \
	);
	if (fd == -1)
		return (ERROR_OPEN);
	if (dup2(fd, 0) == -1)
	{
		close(fd);
		return (ERROR_DUP2);
	}
	if (close(fd) == -1)
		perror("fn: redir_in: close(fd)");
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
		return (ERROR_OPEN);
	}
	if (dup2(fd, 1) == -1)
	{
		close(fd);
		return (ERROR_DUP2);
	}
	if (close(fd) == -1)
		perror("fn: redir_out: close(fd)");
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
		return (ERROR_OPEN);
	}
	if (dup2(fd, 1) == -1)
	{
		close(fd);
		return (ERROR_DUP2);
	}
	if (close(fd) == -1)
		perror("fn: redir_append: close(fd)");
	return (0);
}

static int	redir_here_doc(t_minishell *p_mini, t_ast *ast, size_t i)
{
	int		fd_to_chose;

	fd_to_chose = ((t_dirargs *)ast->arguments.com_args.dir_args.data)[i].\
																filename[0];
	if (dup2(p_mini->fds_here_doc[fd_to_chose], 0) < 0)
	{
		// do stuff ? -> no i dont think so !
		return (ERROR_DUP2);
	}
	return (0);
}
