/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:44:07 by jweber            #+#    #+#             */
/*   Updated: 2025/08/06 15:33:40 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include "minishell.h"
#include "ast.h"
#include <unistd.h>
#include <stdio.h>

static void	close_fd(int *p_fd, int *p_final_ret);

/* This function will
 * increment the number of child to wait for (because we forked just before)
 * set p_mini->last_child_id to the pid of the process just created
 * and close all here_documents that has been opened with this command !
 * to check
 *	-> close fail : DONE ;
*/
int	parent_execution(t_vector dir_args, t_minishell *p_mini, int pid)
{
	size_t	i;
	int		to_close;
	int		final_ret;

	i = 0;
	final_ret = 0;
	p_mini->last_child_id = pid;
	p_mini->nb_child_to_wait++;
	while (i < dir_args.size)
	{
		if (((t_dirargs *)dir_args.data)[i].dir == HEREDOC)
		{
			to_close = ((t_dirargs *)dir_args.data)[i].filename[0];
			close_fd(&p_mini->fds_here_doc[to_close], &final_ret);
		}
		i++;
	}
	return (final_ret);
}

static void	close_fd(int *p_fd, int *p_final_ret)
{
	if (*p_fd > 0)
	{
		if (close(*p_fd) < 0)
		{
			perror("fn : parent_execution : close");
			*p_final_ret = ERROR_CLOSE;
		}
		*p_fd = -1;
	}
}
