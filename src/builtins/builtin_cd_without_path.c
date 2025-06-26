/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_without_path.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:11:54 by jweber            #+#    #+#             */
/*   Updated: 2025/06/26 14:26:27 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_lists_single.h"
#include "ft_string.h"
#include "ft_io.h"
#include "builtins.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

static int	get_path_name(char **p_path_name, t_list *env);

int	builtin_cd_without_path_given(t_minishell *p_mini)
{
	int		ret;
	char	*path_name;
	char	*error_string;
	size_t	path_len;

	ret = get_path_name(&path_name, p_mini->env);
	if (ret != 0)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	path_len = ft_strlen(path_name);
	if (path_name[path_len - 1] == '/')
		path_len--;
	if (path_len > CWD_NAME_MAX_LENGTH)
	{
		ft_printf_fd(2, "%s\n", strerror(ENAMETOOLONG));
		return (1);
	}
	ret = chdir(path_name);
	if (ret == -1)
	{
		error_string = ft_strjoin("cd: ", path_name);
		if (error_string == NULL)
		{
			return (ERROR_MALLOC);
		}
		perror(error_string);
		free(error_string);
		return (1);
	}
	ft_strlcpy(p_mini->cwd_name, path_name, CWD_NAME_MAX_LENGTH);
	path_name = ft_strjoin("PWD=", path_name);
	ret = export_from_string(path_name, p_mini);
	free(path_name);
	return (ret);
}

static int	get_path_name(char **p_path_name, t_list *env)
{
	while (env != NULL)
	{
		if (ft_strcmp(((t_env *)env->content)->key, "HOME") == 0)
		{
			if (((t_env *)env->content)->value != NULL)
			{
				*p_path_name = ((t_env *)env->content)->value;
				return (0);
			}
			else
			{
				return (1);
			}
		}
		env = env->next;
	}
	return (1);
}
