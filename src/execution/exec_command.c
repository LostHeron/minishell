/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:02:34 by jweber            #+#    #+#             */
/*   Updated: 2025/07/04 18:39:41 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "execution.h"
#include "ft_vectors.h"
#include "minishell.h"
#include "ft_io.h"
#include "ft_string.h"
#include "expand.h"
#include <unistd.h>
#include <stdio.h>

static int	get_cmd_type(char **builtins_name, t_vector cmd_args);
static int	restore_fds(t_minishell *p_mini);
static int	case_forking(t_ast *ast, t_minishell *p_mini, int cmd_type);
static int	case_no_forking(t_ast *ast, t_minishell *p_mini);
static void	parent_execution(t_ast *ast, t_minishell *p_mini, int pid);

int	exec_command(t_ast *ast, t_minishell *p_mini)
{
	int		cmd_type;
	int		ret;

	ret = expand(&ast->arguments.com_args.content, *p_mini);
	if (ret != 0)
	{
		return (ret);
	}
	if (ast->arguments.com_args.content.size <= 1)
	{
		return (0);
	}
	ret = expand_redir(&ast->arguments.com_args.dir_args, *p_mini);
	if (ret != 0)
	{
		return (ret);
	}
	cmd_type = get_cmd_type(p_mini->builtins_name, \
						ast->arguments.com_args.content);
	if (p_mini->previous_type == PIPE || cmd_type == CMD_BINARY)
	{
		ret = case_forking(ast, p_mini, cmd_type);
		if (ret != 0)
		{
			return (ret);
		}
	}
	else
	{
		case_no_forking();
		/*
		ret = change_fd_redir(p_mini, ast);
		if (ret != 0)
		{
			// do stuff ?
			//return (ret) ?
			;
		}
		ret = call_builtins(p_mini, ast->arguments.com_args.content);
		if (ret < 0)
		{
			// do stuff ?
			//return (ret) ?
			;
		}
		p_mini->last_error_code = ret;
		ret = restore_fds(p_mini);
		if (ret != 0)
		{
			// do stuff ?
			//return (ret) ?
			;
		}
		p_mini->last_child_id = 0;
		*/
	}
	if (p_mini->first_cmd == 1)
	{
		p_mini->first_cmd = 0;
	}
	return (0);
}

static int	case_forking(t_ast *ast, t_minishell *p_mini, int cmd_type)
{
	int	pid;
	int	ret;

	pid = fork();
	if (pid == -1)
	{
		perror("fn: ... : fork");
		return (ERROR_FORK);
	}
	if (pid == 0)
	{
		p_mini->should_exit = TRUE;
		ret = child_execution(ast, p_mini, cmd_type);
		return (ret);
	}
	else
	{
		parent_execution(ast, p_mini, pid);
		return (0);
	}
}

static void	parent_execution(t_ast *ast, t_minishell *p_mini, int pid)
{
	size_t	i;
	int		to_close;

	i = 0;
	while (i < ast->arguments.com_args.dir_args.size)
	{
		if (((t_dirargs *)ast->arguments.com_args.dir_args.data)[i].dir \
																== HEREDOC)
		{
			to_close = ((t_dirargs *) \
						ast->arguments.com_args.dir_args.data)[i].filename[0];
			if (close(p_mini->fds_here_doc[to_close]) < 0)
				perror("fn : parent_execution : close");
			p_mini->fds_here_doc[to_close] = -1;
		}
		i++;
	}
	p_mini->last_child_id = pid;
}

static int	case_no_forking(t_ast *ast, t_minishell *p_mini)
{
	int	ret_builtin;
	int	ret;

	p_mini->last_child_id = 0;
	ret = change_fd_redir(p_mini, ast);
	if (ret != 0)
		return (ret);
	ret_builtin = call_builtins(p_mini, ast->arguments.com_args.content);
	p_mini->last_error_code = ret;
	ret = restore_fds(p_mini);
	if (ret != 0)
	{
		if (ret_builtin < 0)
			return (ret_builtin);
		return (1);
	}
	if (ret_builtin < 0)
		return (ret_builtin);
}

static int	get_cmd_type(char **builtins_name, t_vector cmd_args)
{
	char	*cmd_name;
	size_t	i;

	if (cmd_args.size < 1)
	{
		ft_putstr_fd("error should not enter here !\n", 2);
		ft_putstr_fd("exec_command.c l:70\n", 2);
		exit(1);
	}
	cmd_name = ((char **)cmd_args.data)[0];
	i = 0;
	while (builtins_name[i] != NULL)
	{
		if (ft_strcmp(builtins_name[i], cmd_name) == 0)
			return (CMD_BUILTIN);
		i++;
	}
	return (CMD_BINARY);
}

static int	restore_fds(t_minishell *p_mini)
{
	if (dup2(p_mini->fd_tty_copy, 2) < 0)
	{
		perror("in restore_fd : dup2(p_mini->fd_stderr, 2)");
		return (ERROR_DUP2);
	}
	if (dup2(p_mini->fd_tty_copy, 1) < 0)
	{
		perror("in restore_fd : dup2(p_mini->fd_stderr, 2)");
		return (ERROR_DUP2);
	}
	if (dup2(p_mini->fd_tty_copy, 0) < 0)
	{
		perror("in restore_fd : dup2(p_mini->fd_stderr, 2)");
		return (ERROR_DUP2);
	}
	return (0);
}
