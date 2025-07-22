/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:37:24 by jweber            #+#    #+#             */
/*   Updated: 2025/07/01 18:15:16 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lists_single.h"
#include "ft_string.h"
#include "minishell.h"
#include "ft_standard.h"
#include "freeing.h"

static int	fill_new_env(t_env *p_new_env, char *env_i);
static int	add_env_i_list(t_minishell *p_mini, char *env_i);
static int	with_equal_sign(t_env *new_env, char *env_i, char *equal_pos);
static int	without_equal_sign(t_env *new_env, char *env_i);
void		add_node_lst(t_minishell *p_mini, t_list *new_node);

/* In case of success :
*	function should return the p_mini->env filled
*  In case of failure :
*	function should return a non null interger, 
*	set p_mini->env to NULL and 
*	have freed all memory it hade allocated
*	to check
*		- add_env_i_list fail : DONE -> OK !
*/
int	init_env(t_minishell *p_mini, char **env)
{
	size_t	i;
	int		ret;

	i = 0;
	p_mini->env = NULL;
	while (env[i] != NULL)
	{
		ret = add_env_i_list(p_mini, env[i]);
		if (ret != 0)
		{
			free_env(p_mini->env);
			return (ret);
		}
		i++;
	}
	return (0);
}

/* to check
 *	- new_env == NULL : DONE -> OK !
 *	- fill_new_env fail : DONE -> OK !
 *	- ft_s_lst_new fail : DONE -> OK !
*/
static int	add_env_i_list(t_minishell *p_mini, char *env_i)
{
	t_env	*new_env;
	t_list	*new_node;
	int		ret;

	new_env = ft_malloc(sizeof(t_env));
	if (new_env == NULL)
		return (ERROR_MALLOC);
	ret = fill_new_env(new_env, env_i);
	if (ret != 0)
	{
		free(new_env);
		return (ret);
	}
	new_node = ft_s_lstnew(new_env);
	if (new_node == NULL)
	{
		free(new_env->key);
		free(new_env->value);
		free(new_env);
		return (ERROR_MALLOC);
	}
	add_node_lst(p_mini, new_node);
	return (0);
}

/*
 * to check :
 *  - without_equal_sign fail : DONE -> OK !
 *  - with_equal_sign fail : DONE -> OK !
*/
static int	fill_new_env(t_env *new_env, char *env_i)
{
	int		ret;
	char	*equal_pos;

	equal_pos = ft_strchr(env_i, '=');
	if (equal_pos == NULL)
	{
		ret = without_equal_sign(new_env, env_i);
		if (ret != 0)
			return (ret);
	}
	else
	{
		ret = with_equal_sign(new_env, env_i, equal_pos);
		if (ret != 0)
			return (ret);
	}
	return (0);
}

/* to check :
 *  - ft_strdup fail : TO DO ;
*/
static int	without_equal_sign(t_env *new_env, char *env_i)
{
	new_env->key = ft_strdup(env_i);
	if (new_env->key == NULL)
	{
		return (ERROR_MALLOC);
	}
	new_env->value = NULL;
	return (0);
}

/* to check :
 *  - first ft_strdup fail : DONE -> OK !
 *  - second ft_strdup fail : DONE -> OK !
*/
static int	with_equal_sign(t_env *new_env, char *env_i, char *equal_pos)
{
	new_env->key = ft_strndup(env_i, equal_pos - env_i);
	if (new_env->key == NULL)
	{
		return (ERROR_MALLOC);
	}
	new_env->value = ft_strdup(equal_pos + 1);
	if (new_env->value == NULL)
	{
		free(new_env->key);
		return (ERROR_MALLOC);
	}
	return (0);
}
