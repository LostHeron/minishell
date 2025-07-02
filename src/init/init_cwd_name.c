/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cwd_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:28:23 by jweber            #+#    #+#             */
/*   Updated: 2025/07/01 18:56:32 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_standard.h"
#include "ft_string.h"
#include <unistd.h>

static t_env	*get_pwd_env(t_list *env);

int	init_cwd_name(t_minishell *p_mini)
{
	char	*ret;
	t_env	*pwd_env;

	p_mini->cwd_name = ft_malloc((CWD_NAME_MAX_LENGTH + 1) * sizeof(char));
	if (p_mini->cwd_name == NULL)
		return (ERROR_MALLOC);
	pwd_env = get_pwd_env(p_mini->env);
	if (pwd_env != NULL)
	{
		if (pwd_env->value != NULL)
		{
			if (access(pwd_env->value, X_OK | F_OK) == 0)
			{
				// should check if lstat // fstat of this file is the same
				ft_strcpy(p_mini->cwd_name, pwd_env->value);
			}
			else
			{
				ret = getcwd(p_mini->cwd_name, CWD_NAME_MAX_LENGTH);
				if (ret == NULL)
				{
					// do stuff ?
					p_mini->cwd_name[0] = '\0';
					// or copy before function call and copy back after function call error ?
					return (1);
				}
				// and set path to current working dir ?
			}
		}
	}
	else
	{
		ret = getcwd(p_mini->cwd_name, CWD_NAME_MAX_LENGTH);
		if (ret == NULL)
		{
			// do stuff ?
			p_mini->cwd_name[0] = '\0';
			// or copy before function call and copy back after function call error ?
			return (1);
		}
		// and set path to current working dir  ?
	}
	// and should add a verification of type $PWD inode == getcwd inode to see if we take from path or else where !
	return (0);
}

static t_env	*get_pwd_env(t_list *env)
{
	while (env != NULL)
	{
		if (ft_strcmp("PWD", ((t_env *)env->content)->key) == 0)
		{
			return (env->content);
		}
		env = env->next;
	}
	return (NULL);
}
