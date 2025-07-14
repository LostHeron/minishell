/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:40:25 by jweber            #+#    #+#             */
/*   Updated: 2025/07/14 13:40:39 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "minishell.h"

char	*get_value(t_list *env, char *key)
{
	if (env == NULL)
		return (NULL);
	while (env != NULL)
	{
		if (ft_strcmp(((t_env *)env->content)->key, key) == 0)
			return (((t_env *)env->content)->value);
		env = env->next;
	}
	return (NULL);
}
