/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:35:23 by jweber            #+#    #+#             */
/*   Updated: 2025/07/29 18:22:23 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lists_single.h"
#include "ft_vectors.h"
#include "minishell.h"
#include "ft_io.h"
#include <stdio.h>

int	builtin_env(t_vector args, t_minishell *p_mini)
{
	t_list	*tmp;

	if (args.size > 2)
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		return (1);
	}
	tmp = p_mini->env;
	while (tmp != NULL)
	{
		if (((t_env *)tmp->content)->value != NULL)
		{
			ft_printf_fd(1, "%s=%s\n",
				((t_env *)tmp->content)->key,
				((t_env *)tmp->content)->value);
		}
		tmp = tmp->next;
	}
	return (0);
}
