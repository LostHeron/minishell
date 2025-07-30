/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:02:33 by jweber            #+#    #+#             */
/*   Updated: 2025/07/30 13:00:08 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include "minishell.h"
#include "ast.h"
#include "execution.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

static int	case_cmd_type_binary(t_ast *ast, t_minishell *p_mini);
static int	case_find_command(t_ast *ast, t_minishell *p_mini, char **p_cmd);
static int	errno_special_value(int errno);

/* at this point, we are already in the child process
 * of the command type node, 
 * we entered here from exec_command call !
 * to do :
 *	-> first close fail : DONE -> OK !
 *	-> make_redirections fail : TO DO ;
 *	-> call_builtins fail : TO DO;
 *	-> case_cmd_type_binary fail : TO DO;
*/
int	child_execution(t_ast *ast, t_minishell *p_mini, int cmd_type)
{
	int			ret;

	ret = close_saved_tty(p_mini);
	if (ret != 0)
	{
		close_on_error(p_mini);
		return (ret);
	}
	ret = make_redirections(ast->arguments.com_args.dir_args, p_mini);
	if (ret != 0)
	{
		return (ret);
	}
	if (((char **)ast->arguments.com_args.content.data)[0] == NULL)
		return (0);
	if (cmd_type == CMD_BUILTIN)
		return (call_builtins(p_mini, ast->arguments.com_args.content));
	else
		return (case_cmd_type_binary(ast, p_mini));
}

static int	case_cmd_type_binary(t_ast *ast, t_minishell *p_mini)
{
	char		*cmd;
	t_vector	new_env;
	int			ret;

	if (((char **)ast->arguments.com_args.content.data)[0][0] == '/'
		|| (((char **)ast->arguments.com_args.content.data)[0][0] == '.'
		&& ((char **)ast->arguments.com_args.content.data)[0][1] == '/'))
	{
		cmd = ((char **)ast->arguments.com_args.content.data)[0];
	}
	else
	{
		ret = case_find_command(ast, p_mini, &cmd);
		if (ret != 0)
			return (ret);
	}
	ret = get_env_from_list(&new_env, p_mini->env);
	if (ret != 0)
		return (ret);
	execve(cmd, ast->arguments.com_args.content.data, new_env.data);
	ft_vector_free(&new_env);
	perror(cmd);
	if (errno == EACCES || errno == ENOENT)
		return (errno_special_value(errno));
	return (1);
}

static int	case_find_command(t_ast *ast, t_minishell *p_mini, char **p_cmd)
{
	int			ret;
	t_vector	path;

	ret = get_path(p_mini, &path);
	if (ret != 0)
	{
		return (ret);
	}
	ret = find_command(ast->arguments.com_args.content.data, path);
	*p_cmd = ((char **)ast->arguments.com_args.content.data)[0];
	ft_vector_free(&path);
	if (ret != 0)
	{
		if (ret < 0)
			return (ret);
		else
		{
			printf("%s: command not found\n", *p_cmd);
			return (127);
		}
	}
	return (0);
}

static int	errno_special_value(int errno)
{
	if (errno == EACCES)
		return (126);
	else
		return (127);
}
