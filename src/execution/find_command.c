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

#include "ft_string.h"
#include "ft_vectors.h"
#include <unistd.h>
#include <sys/stat.h>

/* this command will try to find command using the content in $PATH 
 * environment variable, it will add PATH_1 from $PATH then PATH_2, 
 * ... then PATH_N, each PATH_I in $PATH is separarted by a semicolon (:)
 * if it find a file that exits and that file is not a directory,
 * it will return that file, if that file is a directory, it continue searching
 * if that file exist and is not a directory, it return (0) and set *p_cmd to 
 * that file !
 * if it find no file, it return 127 !
 * and in case of stat fail : what to do ??
*/
int	find_command(char **p_cmd, t_vector path)
{
	size_t		i;
	int			ret;
	char		*new_cmd;
	struct stat	f_stat;

	i = 0;
	while (i < path.size)
	{
		new_cmd = ft_strjoin(((char **)path.data)[i], *p_cmd);
		if (new_cmd == NULL)
			return (ERROR_MALLOC);
		if (access(new_cmd, F_OK) == 0)
		{
			ret = stat(new_cmd, &f_stat);
			if (ret != 0)
			{
				;// do stuff 
			}
			if ((f_stat.st_mode & S_IFMT) == S_IFREG)
			{
				free(*p_cmd);
				*p_cmd = new_cmd;
				return (0);
			}
		}
		free(new_cmd);
		i++;
	}
	if (path.size == 0)
		if (access(*p_cmd, F_OK) == 0)
			return (0);
	return (127);
}
