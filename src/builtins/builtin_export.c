/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:34:56 by jweber            #+#    #+#             */
/*   Updated: 2025/06/26 13:48:25 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include "minishell.h"
#include <stdio.h>

int			builtin_export_with_args(t_vector args, t_minishell *p_mini);
static int	builtin_export_no_args(t_minishell *p_mini);

int	builtin_export(t_vector args, t_minishell *p_mini)
{
	size_t	ret;

	ret = 0;
	if (args.size == 2)
	{
		builtin_export_no_args(p_mini);//builtin_export_no_args(p_mini);
	}
	else
	{
		ret = builtin_export_with_args(args, p_mini);
		if (ret < 0)
		{
			// do stuff ? and exit after
		}
		else if (ret != 0)
		{
			// do stuff ? and continue execution 
		}
	}
	return (ret);
}

static int	builtin_export_no_args(t_minishell *p_mini)
{
	t_list	*tmp;

	tmp = p_mini->env;
	while (tmp != NULL)
	{
		if (((t_env *)tmp->content)->value != NULL)
			printf("declare -x %s=\"%s\"\n", \
			((t_env *)tmp->content)->key, \
			((t_env *)tmp->content)->value);
		else
			printf("declare -x %s\n", \
			((t_env *)tmp->content)->key);
		tmp = tmp->next;
	}
	return (0);
}
