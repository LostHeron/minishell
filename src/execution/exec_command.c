/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:02:34 by jweber            #+#    #+#             */
/*   Updated: 2025/06/16 17:39:36 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft_vectors.h"
#include "minishell.h"
#include "ft_io.h"
#include "ft_string.h"
#include <unistd.h>

static int	get_cmd_type(char **builtins_name, t_vector cmd_args);
static int	call_builtins(t_minishell *p_mini, t_vector cmd_args);

int	exec_command(t_ast *ast, t_minishell *p_mini)
{
	int		pid;
	int		cmd_type;
	int		ret;

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
			ret = child_execution(ast, p_mini);
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
		}
	}
	else
	{
		call_builtins(p_mini, ast->arguments.com_args.content);
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

static int	call_builtins(t_minishell *p_mini, t_vector cmd_args)
{
	char	*cmd_name;
	size_t	i;
	int		ret;

	cmd_name = ((char **)cmd_args.data)[0];
	i = 0;
	while (p_mini->builtins_name[i] != NULL)
	{
		if (ft_strcmp(p_mini->builtins_name[i], cmd_name) == 0)
		{
			ret = p_mini->builtins_func[i](cmd_args, p_mini);
			if (ret != 0)
			{
				//do stuff ?
			}
			return (ret);
		}
		i++;
	}
	return (1);
}
