/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:02:34 by jweber            #+#    #+#             */
/*   Updated: 2025/06/26 13:49:46 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	exec_command(t_ast *ast, t_minishell *p_mini)
{
	int		pid;
	int		cmd_type;
	int		ret;

	ret = expand(&ast->arguments.com_args.content, *p_mini);
	if (ret != 0)
	{
		// do stuff ?
		// return (ret) ?
		;
	}
	ret = expand_redir(&ast->arguments.com_args.dir_args, *p_mini);
	if (ret != 0)
	{
		// do stuff ?
		// return (ret) ?
		;
	}
	cmd_type = get_cmd_type(p_mini->builtins_name, \
						ast->arguments.com_args.content);
	if (p_mini->previous_type == PIPE || cmd_type == CMD_BINARY)
	{
		pid = fork();
		if (pid == -1)
		{
			// see later !
			// return ??
			;
		}
		if (pid == 0)
		{
			ret = child_execution(ast, p_mini, cmd_type);
			if (ret != 0)
			{
				// do stuff;
				// return (ret); ?
			}
		}
		else
		{
			// in parent !
			// do something here ??? je crois pas 
			p_mini->last_child_id = pid;
		}
	}
	else
	{
		ret = change_fd_redir(ast);
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
	}
	return (0);
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
	if (dup2(p_mini->fd_stderr, 2) < 0)
	{
		perror("in restore_fd : dup2(p_mini->fd_stderr, 2)");
		return (1);
	}
	if (dup2(p_mini->fd_stdout, 1) < 0)
	{
		perror("in restore_fd : dup2(p_mini->fd_stderr, 2)");
		return (1);
	}
	if (dup2(p_mini->fd_stdin, 0) < 0)
	{
		perror("in restore_fd : dup2(p_mini->fd_stderr, 2)");
		return (1);
	}
	return (0);
}
