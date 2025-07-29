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

static int	init_path_name(t_minishell *p_mini, char **p_path_name);
static int	get_path_name(char **p_path_name, t_list *env);
static int	call_to_chdir(char *path_name);

/* to check : 
 *	-> init_path_name fail : DONE -> OK !
 *	-> call_to_chdir fail : DONE -> OK !
 *	-> ft_strjoin fail : DONE -> OK !
 *	-> export_from_string fail : DONE -> OK !
*/
int	builtin_cd_without_path_given(t_minishell *p_mini)
{
	int		ret;
	char	*path_name;

	ret = init_path_name(p_mini, &path_name);
	if (ret != 0)
		return (ret);
	ret = call_to_chdir(path_name);
	if (ret != 0)
		return (ret);
	ft_strlcpy(p_mini->cwd_name, path_name, CWD_NAME_MAX_LENGTH);
	path_name = ft_strjoin("PWD=", path_name);
	if (path_name == NULL)
		return (ERROR_MALLOC);
	ret = export_from_string(path_name, p_mini);
	free(path_name);
	return (ret);
}

/* This function return 0 if the environment variable $HOME
 * exisits and its value is not NULL and set *p_path_name 
 * to the value of $HOME
 *
 * if returns 1 if there is no $HOME environment variable
 * of if its value is NULL
 * to check:
 *	-> nothing to check function is safe  and can not fail
*/
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

/* to check : 
 *	-> ft_strjoin fail : DONE -> OK !
 *	-> chdir fail : DONE -> OK !
*/
static int	call_to_chdir(char *path_name)
{
	int		ret;
	char	*error_string;

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
	return (0);
}

/* to check :
 *	-> get_path_name fail : TO DO ;
 *	-> 
*/
static int	init_path_name(t_minishell *p_mini, char **p_path_name)
{
	size_t	path_len;
	int		ret;

	ret = get_path_name(p_path_name, p_mini->env);
	if (ret != 0)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	path_len = ft_strlen(*p_path_name);
	if ((*p_path_name)[path_len - 1] == '/')
		path_len--;
	if (path_len > CWD_NAME_MAX_LENGTH)
	{
		ft_printf_fd(2, "%s\n", strerror(ENAMETOOLONG));
		return (1);
	}
	return (0);
}
