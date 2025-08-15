/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:02:33 by jweber            #+#    #+#             */
/*   Updated: 2025/08/14 13:37:27 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include "minishell.h"
#include "ast.h"
#include "execution.h"
#include <asm-generic/errno-base.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

static int	case_cmd_type_binary(t_ast *ast, t_minishell *p_mini);

/* at this point, we are already in the child process
 * of the command type node, 
 * we entered here from exec_command call !
 * to do :
 *	-> close_saved_tty fail : DONE -> OK !
 *	-> make_redirections fail : DONE -> OK !
 *	-> call_builtins fail : DONE -> OK !
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
		if (ret == ERROR_OPEN)
			return (1);
		return (ret);
	}
	if (((char **)ast->arguments.com_args.content.data)[0] == NULL)
		return (0);
	if (cmd_type == CMD_BUILTIN)
	{
		return (call_builtins(p_mini, ast->arguments.com_args.content));
	}
	else
		return (case_cmd_type_binary(ast, p_mini));
}

static int	case_cmd_type_binary(t_ast *ast, t_minishell *p_mini)
{
	char		*cmd;
	t_vector	new_env;
	int			ret;
	int			execve_errno;

	ret = get_command(ast, p_mini, &cmd);
	if (ret != 0)
		return (ret);
	ret = get_env_from_list(&new_env, p_mini->env);
	if (ret != 0)
		return (ret);
	ret = close_here_doc_fds(p_mini);
	if (ret != 0)
	{
		(void) ret;// do something
	}
	execve(cmd, ast->arguments.com_args.content.data, new_env.data);
	execve_errno = errno;
	perror(cmd);
	ft_vector_free(&new_env);
	if (execve_errno == EACCES || execve_errno == ENOENT
		|| execve_errno == ENOTDIR)
		return (errno_special_value(execve_errno));
	return (execve_errno);
}
