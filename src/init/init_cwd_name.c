/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cwd_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:28:23 by jweber            #+#    #+#             */
/*   Updated: 2025/07/22 13:03:43 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"
#include "ft_standard.h"
#include "ft_string.h"
#include "ft_init.h"
#include <unistd.h>
#include <stdio.h>

static int		free_cwd_name_return(char *cwd_name, int ret);
static t_env	*get_pwd_env(t_list *env);
static int		init_pwd_env_var(t_minishell *p_mini);

/* this function should malloc p_mini->cwd_name
 * to the size of CWD_NAME_MAX_LENGTH
 * in case of memory allocation fail : 
 *	return ERROR_MALLOC
 * in case of success :
 *	return the string p_mini->cwd_name should be filled
 *	with the correct current working directory of the shell
 *	to check :
 *		-> ft_malloc fail : DONE -> OK !
 *		-> case_pwd_env_not_null : DONE -> OK !
 *		-> case_pwd_env_null : DONE -> OK !
 *		-> init_pwd_env_var : DONE -> OK !
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
			return (free_cwd_name_return(p_mini->cwd_name, ret));
	}
	else
	{
		ret = case_pwd_env_null(p_mini);
		if (ret != 0)
			return (free_cwd_name_return(p_mini->cwd_name, ret));
	}
	ret = init_pwd_env_var(p_mini);
	if (ret != 0)
		free(p_mini->cwd_name);
	return (ret);
}

static int	free_cwd_name_return(char *cwd_name, int ret)
{
	free(cwd_name);
	return (ret);
}

/* to check 
 *	-> ft_strjoin fail : DONE -> OK !
 *	-> export_from_string fail : DONE -> OK !
*/
static int	init_pwd_env_var(t_minishell *p_mini)
{
	char	*pwd_env_str;
	int		ret;

	pwd_env_str = ft_strjoin("PWD=", p_mini->cwd_name);
	if (pwd_env_str == NULL)
		return (ERROR_MALLOC);
	ret = export_from_string(pwd_env_str, p_mini);
	free(pwd_env_str);
	return (ret);
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
