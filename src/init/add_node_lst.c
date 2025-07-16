/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:04:49 by jweber            #+#    #+#             */
/*   Updated: 2025/07/01 18:09:06 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_lists_single.h"
#include "ft_string.h"

static void	case_env_not_null(t_minishell *p_mini, t_list *new_node);

void	add_node_lst(t_minishell *p_mini, t_list *new_node)
{
	if (p_mini->env == NULL)
	{
		p_mini->env = new_node;
	}
	else
	{
		case_env_not_null(p_mini, new_node);
	}
	return ;
}

static void	case_env_not_null(t_minishell *p_mini, t_list *new_node)
{
	t_list	*tmp;

	if (ft_strcmp(((t_env *)p_mini->env->content)->key, \
((t_env *)new_node->content)->key) > 0)
	{
		new_node->next = p_mini->env;
		p_mini->env = new_node;
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
		tmp->next = new_node;
	}
	return ;
}
