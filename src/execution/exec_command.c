/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:02:34 by jweber            #+#    #+#             */
/*   Updated: 2025/07/15 11:59:02 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "execution.h"
#include "ft_vectors.h"
#include "minishell.h"
#include "ft_string.h"
#include "expand.h"
#include <unistd.h>
#include <stdio.h>

static int	get_cmd_type(char **builtins_name, t_vector cmd_args);

int	exec_command(t_ast *ast, t_minishell *p_mini)
{
	int		cmd_type;
	int		ret;

	ret = expand(&ast->arguments.com_args.content, *p_mini);
	if (ret != 0)
		return (ret);
	if (ast->arguments.com_args.content.size <= 1)
		return (0);
	ret = expand_redir(&ast->arguments.com_args.dir_args, *p_mini);
	if (ret != 0)
		return (ret);
	cmd_type = get_cmd_type(p_mini->builtins_name,
			ast->arguments.com_args.content);
	if (p_mini->previous_type == PIPE || cmd_type == CMD_BINARY)
	{
		ret = case_forking(ast, p_mini, cmd_type);
		if (ret != 0)
			return (ret);
	}
	else
		ret = case_no_forking(ast, p_mini);
	if (p_mini->first_cmd == 1)
		p_mini->first_cmd = 0;
	return (ret);
}

static int	get_cmd_type(char **builtins_name, t_vector cmd_args)
{
	char	*cmd_name;
	size_t	i;

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
