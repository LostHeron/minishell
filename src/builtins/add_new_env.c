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

/* This function malloc a new structure t_env, and associates
 * the new t_env, key argument to new_key and value argument to new_value
 * it then creates a new_node (of type t_list) usgin ft_s_lstnew function
 * and associat t_list ->content to be a pointer to the t_env structure 
 * created just before
 * It then add this new t_list to the already existing chained list
 * int p_mini->env and at the right place (sorted with ASCII, using the 
 * function add_node_lst)
 * In case of failure : 
 *	return (ERROR_MALLOC) and free memory allocated inside this function
 * In case of success : 
 *	return (0) and have the new t_list created and added to the list
 * to check
 *	-> ft_malloc fail : DONE -> OK !
 *	-> ft_s_lstnew fail : DONE -> OK !
*/
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
		if (ft_strcmp(((t_env *)p_mini->env->content)->key,
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
		if (ft_strcmp(((t_env *)tmp->next->content)->key,
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
