/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 13:34:35 by jweber            #+#    #+#             */
/*   Updated: 2025/08/14 13:36:31 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "execution.h"
#include "ft_string.h"
#include "minishell.h"
#include "ft_io.h"
#include <asm-generic/errno.h>
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

static int	case_find_command(t_ast *ast, t_minishell *p_mini, char **p_cmd);
static int	check_cmd(char **p_cmd);

/* This function will try to get a command and return it to the user
 * In case of SUCCESS :
 *		-> return 0 if a command was found, 
 *		this command should then be the one executed by execve
 *		-> return 127 or 126 depending on why no command could be found
 * In case of FAILURE :
 *		-> return negative integer and stop execution
 * to check 
 *	-> case_find_command fail : DONE -> OK !
 *	-> check_cmd fail : DONE -> OK !
*/
int	get_command(t_ast *ast, t_minishell *p_mini, char **p_cmd)
{
	int			ret;
	char		*first;

	first = ((char **)ast->arguments.com_args.content.data)[0];
	if (ft_strchr(first, '/') != NULL)
		*p_cmd = ((char **)ast->arguments.com_args.content.data)[0];
	else
	{
		ret = case_find_command(ast, p_mini, p_cmd);
		if (ret != 0)
			return (ret);
	}
	return (check_cmd(p_cmd));
}

/* to check
 *	-> get_path fail : DONE -> OK !
 *	-> find_command fail : DONE -> OK !
*/
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

/* check if cmd is directory or not
 * to check :
 *	-> stat fail : DONE -> OK !
*/
static int	check_cmd(char **p_cmd)
{
	struct stat	f_stat;
	int			ret;
	int			tmp_errno;

	if (access(*p_cmd, F_OK) < 0)
	{
		tmp_errno = errno;
		perror(*p_cmd);
		return (errno_special_value(tmp_errno));
	}
	ret = stat(*p_cmd, &f_stat);
	if (ret != 0)
	{
		perror("stat");
		return (ERROR_STAT);
	}
	if ((f_stat.st_mode & S_IFMT) == S_IFDIR)
	{
		errno = EISDIR;
		perror(*p_cmd);
		return (126);
	}
	return (0);
}
