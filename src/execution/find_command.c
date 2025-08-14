/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:01:57 by jweber            #+#    #+#             */
/*   Updated: 2025/07/21 14:26:55 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_string.h"
#include "ft_vectors.h"
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>

static int	try_find_cmd(char *path_i, char **p_cmd, int *p_break);
static int	case_file_exists(char *new_cmd, char **p_cmd, int *p_should_return);

/* this command will try to find command using the content in $PATH 
 * environment variable, it will add PATH_1 from $PATH then PATH_2, 
 * ... then PATH_N, each PATH_I in $PATH is separarted by a semicolon (:)
 * if it find a file that exits and that file is not a directory,
 * it will return that file, if that file is a directory, it continue searching
 * if that file exist and is not a directory, it return (0) and set *p_cmd to 
 * that file !
 * in case of SUCCESS : 
 *		-> if it finds a file : return 0
 *		-> if it do not finds file : return 127
 * in case of FAILURE : 
 *		-> return a negative integer
*/
int	find_command(char **p_cmd, t_vector path)
{
	size_t	i;
	int		ret;
	int		should_exit;

	i = 0;
	should_exit = FALSE;
	while (i < path.size)
	{
		ret = try_find_cmd(((char **)path.data)[i], p_cmd, &should_exit);
		if (should_exit == TRUE)
			return (ret);
		i++;
	}
	if (path.size == 0)
		if (access(*p_cmd, F_OK) == 0)
			return (0);
	return (127);
}

static int	try_find_cmd(char *path_i, char **p_cmd, int *p_should_return)
{
	int			ret;
	char		*new_cmd;

	new_cmd = ft_strjoin(path_i, *p_cmd);
	if (new_cmd == NULL)
	{
		*p_should_return = TRUE;
		return (ERROR_MALLOC);
	}
	if (access(new_cmd, F_OK) == 0)
	{
		ret = case_file_exists(new_cmd, p_cmd, p_should_return);
		if (*p_should_return == TRUE)
			return (ret);
	}
	free(new_cmd);
	return (0);
}

static int	case_file_exists(char *new_cmd, char **p_cmd, int *p_should_return)
{
	int			ret;
	struct stat	f_stat;

	ret = stat(new_cmd, &f_stat);
	if (ret != 0)
	{
		perror("stat");
		*p_should_return = TRUE;
		free(new_cmd);
		return (ret);
	}
	if ((f_stat.st_mode & S_IFMT) == S_IFREG)
	{
		*p_should_return = TRUE;
		free(*p_cmd);
		*p_cmd = new_cmd;
		return (0);
	}
	return (0);
}
