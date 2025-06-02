/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:37:24 by jweber            #+#    #+#             */
/*   Updated: 2025/06/02 18:11:05 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lists_single.h"
#include "ft_string.h"
#include "minishell.h"
#include "src/libft/src/io/get_next_line/get_next_line.h"

static int	fill_new_env(t_env *p_new_env, char *env_i);

int	init_env(t_minishell *p_mini, char **env)
{
	size_t	i;
	char	*env_cpy;
	t_env	*new_env;
	t_list	*new_node;

	i = 0;
	p_mini->env = NULL;
	while (env[i] != NULL)
	{
		new_env = malloc(sizeof(t_env));
		if (p_new_env == NULL)
		{
			//do stuff;
			return (ERROR_MALLOC);
		}
		ret = fill_new_env(new_env, env[i]);
		if (ret != 0)
		{
			// do stuff
			return (ret);
		}
		env_cpy = ft_strndup(env[i]);
		if (env_cpy == NULL)
		{
			//clear_lst(lst);
			free(new_env);
			return (ERROR_MALLOC);
		}
		new_node = ft_s_lstnew(env_cpy);
		if (new_node == NULL)
		{
			//clear_lst(lst);
			free(new_env);
			free(env_cpy);
			return (ERROR_MALLOC);
		}
	}
	return (0);
}

static int	fill_new_env(t_env *new_env, char *env_i)
{
	char	*equal_pos;

	equal_pos = ft_strchr(env_i, '=');
	if (equal_pos == NULL)
	{
		new_env->key = ft_strdup(env_i);
		if (new_env->key == NULL)
		{
			//do stuff;
			return (ERROR_MALLOC);
		}
		new_env->value = NULL;
	}
	else
	{
		new_env->key = ft_strndup(env_i, equal_pos - env_i);
		if (new_env->key == NULL)
		{
			//do stuff;
			return (ERROR_MALLOC);
		}
		new_env->value = ft_strdup(equal_pos + 1);
		if (new_env->key == NULL)
		{
			//do stuff;
			return (ERROR_MALLOC);
		}
	}
}
