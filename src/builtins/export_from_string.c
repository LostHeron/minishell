/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_from_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:44:09 by jweber            #+#    #+#             */
/*   Updated: 2025/06/20 15:51:59 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lists_single.h"
#include "ft_string.h"
#include "builtins.h"
#include "minishell.h"

/* 
 * This function expects a valid string format for 
 * the string it is passed of format :
 * starting by an alpha or an '_';
 * and next char being eith alnum of '_';
*/
int	export_from_string(char *str, t_minishell *p_mini)
{
	int		ret;
	char	*new_key;
	char	*new_value;
	t_list	*env;

	ret = get_new_key_value(str, &new_key, &new_value);
	if (ret != 0)
		return (ret);
	env = p_mini->env;
	while (env != NULL)
	{
		if (ft_strcmp(new_key, ((t_env *)env->content)->key) == 0)
		{
			if (new_value != NULL)
			{
				free(((t_env *)env->content)->value);
				((t_env *)env->content)->value = new_value;
				free(new_key);
				return (0);
			}
			else
			{
				free(new_value);
				free(new_key);
				return (0);
			}
		}
		env = env->next;
	}
	ret = add_new_env(new_key, new_value, p_mini);
	if (ret != 0)
	{
		free(new_key);
		free(new_value);
		return (ret);
	}
	return (0);
}
