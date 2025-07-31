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
#include "builtins.h"
#include "execution.h"
#include "ft_vectors.h"
#include "minishell.h"
#include "ft_string.h"
#include "expand.h"
#include <unistd.h>
#include <stdio.h>

static int	expansion(t_ast *ast, t_minishell *p_mini);
static int	get_cmd_type(char **builtins_name, t_vector cmd_args);
static int	change_underscore_var(t_minishell *p_mini, t_vector args);

/* to check :
 *	-> expand fail : DONE -> OK !
 *	-> expand_redir fail : DONE -> OK !
 *	-> case_forking fail : DONE -> OK !
 *	-> case_no_forking fail : TO DO ;
*/
int	exec_command(t_ast *ast, t_minishell *p_mini)
{
	int		cmd_type;
	int		ret;

	ret = expansion(ast, p_mini);
	if (ret != 0)
		return (ret);
	cmd_type = get_cmd_type(p_mini->builtins_name,
			ast->arguments.com_args.content);
	if (p_mini->previous_type != PIPE)
	{
		if (change_underscore_var(p_mini, ast->arguments.com_args.content) < 0)
			return (ERROR_MALLOC);
	}
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
	if (cmd_name == NULL)
		return (CMD_BUILTIN);
	i = 0;
	while (builtins_name[i] != NULL)
	{
		if (ft_strcmp(builtins_name[i], cmd_name) == 0)
			return (CMD_BUILTIN);
		i++;
	}
	return (CMD_BINARY);
}

static int	change_underscore_var(t_minishell *p_mini, t_vector args)
{
	char	*str;
	int		ret;

	if (args.size >= 2)
	{
		str = "_=";
		str = ft_strjoin(str, ((char **)args.data)[args.size - 2]);
		if (str == NULL)
			return (ERROR_MALLOC);
		ret = export_from_string(str, p_mini);
		free(str);
		return (ret);
	}
	else
		return (0);
}

static int	expansion(t_ast *ast, t_minishell *p_mini)
{
	int	ret;

	ret = expand(&ast->arguments.com_args.content, *p_mini);
	if (ret != 0)
		return (ret);
	ret = expand_redir(&ast->arguments.com_args.dir_args, *p_mini);
	if (ret != 0)
	{
		p_mini->last_error_code = 1;
		return (ret);
	}
	return (0);
}
