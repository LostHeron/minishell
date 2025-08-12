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

static void		try_remove_key(char *key_to_remove, t_minishell *p_mini);
static t_list	*get_env_previous_free(char *str, t_list *tmp);
static void		case_head(t_minishell *p_mini);
static void		case_not_head(t_list *prev_env);

/* to check
 *	-> NOTHING : this builtin have not failure points
*/
int	builtin_unset(t_vector args, t_minishell *p_mini)
{
	size_t	i;
	char	*key_to_remove;

	i = 1;
	while (i < args.size - 1)
	{
		key_to_remove = ((char **)args.data)[i];
		if (p_mini->env != NULL)
			try_remove_key(key_to_remove, p_mini);
		i++;
	}
	return (0);
}

static void	try_remove_key(char *key_to_remove, t_minishell *p_mini)
{
	t_list	*prev_env;

	if (ft_strcmp(key_to_remove, ((t_env *)p_mini->env->content)->key) == 0)
	{
		case_head(p_mini);
		return ;
	}
	prev_env = get_env_previous_free(key_to_remove, p_mini->env);
	if (prev_env != NULL)
		case_not_head(prev_env);
	return ;
}

static t_list	*get_env_previous_free(char *key_to_remove, t_list *tmp)
{
	if (tmp == NULL)
		return (NULL);
	while (tmp->next != NULL)
	{
		if (ft_strcmp(key_to_remove, ((t_env *)tmp->next->content)->key) == 0)
		{
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

static void	case_head(t_minishell *p_mini)
{
	t_list	*tmp;

	tmp = p_mini->env;
	p_mini->env = tmp->next;
	free(((t_env *)tmp->content)->key);
	free(((t_env *)tmp->content)->value);
	free(tmp->content);
	free(tmp);
}

static void	case_not_head(t_list *prev_env)
{
	t_list	*tmp;

	tmp = prev_env->next;
	prev_env->next = prev_env->next->next;
	free(((t_env *)tmp->content)->key);
	free(((t_env *)tmp->content)->value);
	free(tmp->content);
	free(tmp);
}
