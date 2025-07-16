/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_here_doc_fds.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:22:21 by jweber            #+#    #+#             */
/*   Updated: 2025/07/15 11:19:09 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

int	close_here_doc_fds(t_minishell *p_mini)
{
	size_t	fd_i;

	fd_i = 0;
	while (fd_i < NB_MAX_HERE_DOC)
	{
		if (p_mini->fds_here_doc[fd_i] > 0)
		{
			if (close(p_mini->fds_here_doc[fd_i]) < 0)
			{
				perror(\
		"in redir_here_doc : close(p_mini->fds_here_doc[fd_to_chose])\n");
			}
		}
		fd_i++;
	}
	return (0);
}
