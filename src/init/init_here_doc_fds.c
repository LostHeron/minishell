/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_here_doc_fds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 10:20:27 by jweber            #+#    #+#             */
/*   Updated: 2025/08/06 10:21:21 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_here_doc_fds(t_minishell *p_mini)
{
	size_t	i;

	i = 0;
	while (i < NB_MAX_HERE_DOC)
	{
		p_mini->fds_here_doc[i] = -1;
		i++;
	}
	return ;
}
