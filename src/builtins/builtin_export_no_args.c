/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_no_args.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:11:31 by jweber            #+#    #+#             */
/*   Updated: 2025/07/16 17:12:29 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	builtin_export_no_args(t_minishell *p_mini)
{
	t_list	*tmp;

	tmp = p_mini->env;
	while (tmp != NULL)
	{
		if (((t_env *)tmp->content)->value != NULL)
		{
			printf("export %s=\"%s\"\n", \
((t_env *)tmp->content)->key, \
((t_env *)tmp->content)->value);
		}
		else
		{
			printf("export %s\n", ((t_env *)tmp->content)->key);
		}
		tmp = tmp->next;
	}
	return (0);
}
