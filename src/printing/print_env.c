/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:19:05 by jweber            #+#    #+#             */
/*   Updated: 2025/07/29 18:23:13 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_lists_single.h"
#include "minishell.h"
#include "ft_io.h"

void	print_env(t_minishell *p_mini)
{
	t_list	*tmp;

	ft_printf_fd(1, "in print_env !\n");
	fflush(stdout);
	tmp = p_mini->env;
	while (tmp != NULL)
	{
		ft_printf_fd(1, "key = %s\n", ((t_env *)tmp->content)->key);
		ft_printf_fd(1, "value = %s\n", ((t_env *)tmp->content)->value);
		ft_printf_fd(1, "\n");
		tmp = tmp->next;
	}
}
