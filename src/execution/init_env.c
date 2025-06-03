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
#include "ft_standard.h"

static int	fill_new_env(t_env *p_new_env, char *env_i);
static void	add_node_lst(t_minishell *p_mini, t_list *new_node);
static int	with_equal_sign(t_env *new_env, char *env_i, char *equal_pos);
static int	without_equal_sign(t_env *new_env, char *env_i);

/* In case of success :
*	function should return the p_mini->env filled
*  In case of failure :
*	function should return a p_mini->env = NULL and 
*	have freed all memory it hade allocated
*/
int	init_env(t_minishell *p_mini, char **env)
{
	size_t	i;
	t_env	*new_env;
	t_list	*new_node;
	int		ret;

	i = 0;
	p_mini->env = NULL;
	while (env[i] != NULL)
	{
		new_env = ft_malloc(sizeof(t_env));
		if (new_env == NULL)
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
		new_node = ft_s_lstnew(new_env);
		if (new_node == NULL)
		{
			// do stuff
			return (ERROR_MALLOC);
		}
		add_node_lst(p_mini, new_node);
		i++;
	}
	return (0);
}

static int	fill_new_env(t_env *new_env, char *env_i)
{
	int		ret;
	char	*equal_pos;

	equal_pos = ft_strchr(env_i, '=');
	if (equal_pos == NULL)
	{
		ret = without_equal_sign(new_env, env_i);
		if (ret != 0)
		{
			// do stuff
			return (ret);
		}
	}
	else
	{
		ret = with_equal_sign(new_env, env_i, equal_pos);
		if (ret != 0)
		{
			// do stuff
			return (ret);
		}
	}
	return (0);
}

static void	add_node_lst(t_minishell *p_mini, t_list *new_node)
{
	t_list	*tmp;

	if (p_mini->env == NULL)
	{
		p_mini->env = new_node;
		return ;
	}
	else
	{
		if (ft_strcmp(((t_env *)p_mini->env->content)->key, \
				((t_env *)new_node->content)->key) > 0)
		{
			new_node->next = p_mini->env;
			p_mini->env = new_node;
			return ;
		}
		else
		{
			tmp = p_mini->env;
			while (tmp->next != NULL)
			{
				if (ft_strcmp(((t_env *)tmp->next->content)->key, \
							((t_env *)new_node->content)->key) > 0)
				{
					new_node->next = tmp->next;
					tmp->next = new_node;
					return ;
				}
				tmp = tmp->next;
			}
			new_node->next = tmp->next;
			tmp->next = new_node;
			return ;
		}
	}
}

static int	without_equal_sign(t_env *new_env, char *env_i)
{
	new_env->key = ft_strdup(env_i);
	if (new_env->key == NULL)
	{
		//do stuff;
		return (ERROR_MALLOC);
	}
	new_env->value = NULL;
	return (0);
}

static int	with_equal_sign(t_env *new_env, char *env_i, char *equal_pos)
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
	return (0);
}
