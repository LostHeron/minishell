/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cwd_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:28:23 by jweber            #+#    #+#             */
/*   Updated: 2025/07/03 14:50:58 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_standard.h"
#include "ft_string.h"
#include "ft_init.h"
#include <unistd.h>
#include <stdio.h>

static int		case_pwd_env_not_null(t_minishell *p_mini, t_env *pwd_env);
static int		case_pwd_env_null(t_minishell *p_mini);
static t_env	*get_pwd_env(t_list *env);

/* this function should malloc p_mini->cwd_name
 * to the size of CWD_NAME_MAX_LENGTH
 * in case of memory allocation fail : 
 *	return ERROR_MALLOC
 * in case of success :
 *	return the string p_mini->cwd_name should be filled
 *	with the correct current working directory of the shell
*/
int	init_cwd_name(t_minishell *p_mini)
{
	t_env	*pwd_env;
	int		ret;

	p_mini->cwd_name = ft_malloc((CWD_NAME_MAX_LENGTH + 1) * sizeof(char));
	if (p_mini->cwd_name == NULL)
		return (ERROR_MALLOC);
	pwd_env = get_pwd_env(p_mini->env);
	if (pwd_env != NULL)
	{
		ret = case_pwd_env_not_null(p_mini, pwd_env);
		if (ret != 0)
			free(p_mini->cwd_name);
		return (ret);
	}
	else
	{
		ret = case_pwd_env_null(p_mini);
		if (ret != 0)
			free(p_mini->cwd_name);
		return (ret);
	}
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

static int	case_pwd_env_not_null(t_minishell *p_mini, t_env *pwd_env)
{
	char	*ret_getcwd;

	if (pwd_env->value != NULL)
	{
		return (case_value_not_null(p_mini, pwd_env->value));
	}
	else
	{
		ret_getcwd = getcwd(p_mini->cwd_name, CWD_NAME_MAX_LENGTH);
		if (ret_getcwd == NULL)
		{
			perror("fn : initi_cwd_name : getcwd :");
			return (1);
		}
	}
	return (0);
}

static int	case_pwd_env_null(t_minishell *p_mini)
{
	char	*ret_getcwd;

	ret_getcwd = getcwd(p_mini->cwd_name, CWD_NAME_MAX_LENGTH);
	if (ret_getcwd == NULL)
	{
		perror("fn : case_pwd_env_null : getcwd");
		return (1);
	}
	return (0);
}
