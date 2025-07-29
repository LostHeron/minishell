/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_no_args.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:11:31 by jweber            #+#    #+#             */
/*   Updated: 2025/07/29 18:23:58 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_io.h"
#include <stdio.h>

int	builtin_export_no_args(t_minishell *p_mini)
{
	t_list	*tmp;

	tmp = p_mini->env;
	while (tmp != NULL)
	{
		if (((t_env *)tmp->content)->value != NULL)
		{
			ft_printf_fd(1, "export %s=\"%s\"\n", \
					((t_env *)tmp->content)->key, \
					((t_env *)tmp->content)->value);
		}
		else
		{
			ft_printf_fd(1, "export %s\n", ((t_env *)tmp->content)->key);
		}
		tmp = tmp->next;
	}
	return (0);
}
