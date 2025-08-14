/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:02:33 by jweber            #+#    #+#             */
/*   Updated: 2025/07/30 13:14:47 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"
#include "ft_vectors.h"
#include "minishell.h"
#include "ast.h"
#include "execution.h"
#include "ft_string.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>

static int	case_cmd_type_binary(t_ast *ast, t_minishell *p_mini);
static int	get_command(t_ast *ast, t_minishell *p_mini, char **p_cmd);
static int	case_find_command(t_ast *ast, t_minishell *p_mini, char **p_cmd);
static int	errno_special_value(int execve_errno);

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
		// do something
	}
	execve(cmd, ast->arguments.com_args.content.data, new_env.data);
	execve_errno = errno;
	ft_vector_free(&new_env);
	perror(cmd);
	if (execve_errno == EACCES || execve_errno == ENOENT)
		return (errno_special_value(execve_errno));
	return (execve_errno);
}

/* function will search for the command,
 * if command start with "/" or "./" or "../" or is equal to ".."
 * or is equal to ".", the command will return error and print to the user
 * that the command is a directory !
*/
static int	get_command(t_ast *ast, t_minishell *p_mini, char **p_cmd)
{
	int			ret;
	char		*first;
	struct stat	f_stat;

	first = ((char **)ast->arguments.com_args.content.data)[0];
	if (ft_strchr(first, '/') != NULL)
		*p_cmd = ((char **)ast->arguments.com_args.content.data)[0];
	else
	{
		ret = case_find_command(ast, p_mini, p_cmd);
		if (ret != 0)
			return (ret);
	}
	if (access(*p_cmd, F_OK) < 0)
	{
		perror(*p_cmd);
		return (127);
	}
	ret = stat(*p_cmd, &f_stat);
	if (ret != 0)
	{
		perror("stat");
		return (ret);// do stuff 
	}
	if ((f_stat.st_mode & S_IFMT) == S_IFDIR)
	{
		errno = EISDIR;
		perror(*p_cmd);
		return (126);
	}
	// check if  *p_cmd is a directory with stat,
	// if it is, then perror is a directory and return 126
	return (0);
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
			ft_printf_fd(2, "%s: command not found\n", *p_cmd);
			return (127);
		}
	}
	return (0);
}

static int	errno_special_value(int execve_errno)
{
	if (execve_errno == EACCES)
		return (126);
	else
		return (127);
}
