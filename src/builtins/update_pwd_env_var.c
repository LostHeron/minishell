/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_pwd_env_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:18:15 by jweber            #+#    #+#             */
/*   Updated: 2025/07/18 14:24:17 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_string.h"
#include "builtins.h"

static t_env	*get_pwd_env(t_list *env);

int	update_pwd_env_var(t_minishell *p_mini)
{
	int		ret;
	t_env	*pwd_env;
	char	*string_pwd;

	ret = 0;
	pwd_env = get_pwd_env(p_mini->env);
	if (pwd_env != NULL)
	{
		string_pwd = ft_strjoin("PWD=", p_mini->cwd_name);
		if (string_pwd == NULL)
			return (ERROR_MALLOC);
		ret = export_from_string(string_pwd, p_mini);
		free(string_pwd);
	}
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
