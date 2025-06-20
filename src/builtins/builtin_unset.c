/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:34:29 by jweber            #+#    #+#             */
/*   Updated: 2025/06/16 17:35:23 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_string.h"

static t_list	*get_env_previous_free(char *str, t_list *tmp);

int	builtin_unset(t_vector args, t_minishell *p_mini)
{
	size_t	i;
	t_list	*prev_env;
	t_list	*tmp;

	i = 1;
	prev_env = p_mini->env;
	while (i < args.size - 1)
	{
		prev_env = get_env_previous_free(((char **)args.data)[i], p_mini->env);
		if (prev_env != NULL)
		{
			if (prev_env == p_mini->env)
			{
				tmp = p_mini->env;
				p_mini->env = tmp->next;
				free(((t_env *)tmp->content)->key);
				free(((t_env *)tmp->content)->value);
				free(tmp->content);
				free(tmp);
			}
			else
			{
				tmp = prev_env->next;
				prev_env->next = tmp->next;
				free(((t_env *)tmp->content)->key);
				free(((t_env *)tmp->content)->value);
				free(tmp->content);
				free(tmp);
			}
		}
		i++;
	}
	return (0);
}

static t_list	*get_env_previous_free(char *str, t_list *tmp)
{
	if (tmp == NULL)
		return (NULL);
	if (ft_strcmp(str, ((t_env *)tmp->content)->key) == 0)
	{
		return (tmp);
	}
	while (tmp->next != NULL)
	{
		if (ft_strcmp(str, ((t_env *)tmp->next->content)->key) == 0)
		{
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
