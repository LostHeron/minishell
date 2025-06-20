/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_new_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:30:57 by jweber            #+#    #+#             */
/*   Updated: 2025/06/20 15:52:55 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_standard.h"
#include "ft_string.h"

static void	add_node_lst(t_minishell *p_mini, t_list *new_node);
static void	add_node_lst_after_head(t_minishell *p_mini, t_list *new_node);

int	add_new_env(char *new_key, char *new_value, t_minishell *p_mini)
{
	t_env	*new_env;
	t_list	*new_node;

	new_env = ft_malloc(sizeof(t_env));
	if (new_env == NULL)
		return (ERROR_MALLOC);
	new_env->key = new_key;
	new_env->value = new_value;
	new_node = ft_s_lstnew(new_env);
	if (new_node == NULL)
	{
		free(new_env);
		return (ERROR_MALLOC);
	}
	add_node_lst(p_mini, new_node);
	return (0);
}

static void	add_node_lst(t_minishell *p_mini, t_list *new_node)
{
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
			add_node_lst_after_head(p_mini, new_node);
			return ;
		}
	}
	return ;
}

static void	add_node_lst_after_head(t_minishell *p_mini, t_list *new_node)
{
	t_list	*tmp;

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
	tmp->next = new_node;
}
