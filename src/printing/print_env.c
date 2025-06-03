/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:19:05 by jweber            #+#    #+#             */
/*   Updated: 2025/06/03 16:33:20 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_lists_single.h"
#include "minishell.h"

void	print_env(t_minishell *p_mini)
{
	t_list	*tmp;

	printf("in print_env !\n");
	fflush(stdout);
	tmp = p_mini->env;
	while (tmp != NULL)
	{
		printf("key = %s\n", ((t_env *)tmp->content)->key);
		printf("value = %s\n", ((t_env *)tmp->content)->value);
		printf("\n");
		tmp = tmp->next;
	}
}
