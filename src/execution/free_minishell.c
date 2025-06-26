/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:47:21 by jweber            #+#    #+#             */
/*   Updated: 2025/06/26 14:24:44 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lists_single.h"
#include "ft_vectors.h"
#include "minishell.h"
#include <unistd.h>

static void	my_free(t_list *lst);

void	free_minishell(t_minishell *p_mini)
{
	close(p_mini->fd_stdin);
	close(p_mini->fd_stdout);
	close(p_mini->fd_stderr);
	my_free(p_mini->env);
	free(p_mini->cwd_name);
}

static void	my_free(t_list *lst)
{
	t_list	*tmp;

	while (lst != NULL)
	{
		tmp = lst;
		lst = lst->next;
		free(((t_env *)tmp->content)->key);
		free(((t_env *)tmp->content)->value);
		free(tmp->content);
		free(tmp);
	}
}
