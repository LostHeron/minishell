/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:19:05 by jweber            #+#    #+#             */
/*   Updated: 2025/07/31 11:36:58 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lists_single.h"
#include "minishell.h"
#include "ft_io.h"

void	print_env(t_minishell *p_mini)
{
	t_list	*tmp;

	ft_printf_fd(2, "in print_env !\n");
	tmp = p_mini->env;
	while (tmp != NULL)
	{
		ft_printf_fd(2, "key = %s\n", ((t_env *)tmp->content)->key);
		ft_printf_fd(2, "value = %s\n", ((t_env *)tmp->content)->value);
		ft_printf_fd(2, "\n");
		tmp = tmp->next;
	}
}
