/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_from_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:44:09 by jweber            #+#    #+#             */
/*   Updated: 2025/07/18 13:39:46 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lists_single.h"
#include "ft_string.h"
#include "builtins.h"
#include "minishell.h"

static int	change_existing_env(t_list *env, char *new_key, char *new_value);

/* 
 * This function expects a valid string format for 
 * the string it is passed of format :
 * starting by an alpha or an '_';
 * and next char being eith alnum or '_' until an '=' sign
 * then can have any kind of char 
 * to check : 
 *	 -> get_new_key_value fail : DONE -> OK ;
 *	 -> change_existing_env : DONE -> OK ; (always succed)
 *	 -> add_new_env : DONE -> OK ;
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
			return (change_existing_env(env, new_key, new_value));
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

/* this function only return 0
 *	to reduce calling function line length !
 * but this function always succed 
*/
static int	change_existing_env(t_list *env, char *new_key, char *new_value)
{
	free(new_key);
	if (new_value != NULL)
	{
		free(((t_env *)env->content)->value);
		((t_env *)env->content)->value = new_value;
	}
	else
	{
		free(new_value);
	}
	return (0);
}
