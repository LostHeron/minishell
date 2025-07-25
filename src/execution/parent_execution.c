/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:44:07 by jweber            #+#    #+#             */
/*   Updated: 2025/07/23 17:35:00 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"
#include <unistd.h>
#include <stdio.h>

void	parent_execution(t_ast *ast, t_minishell *p_mini, int pid)
{
	size_t	i;
	int		to_close;

	i = 0;
	p_mini->last_child_id = pid;
	p_mini->nb_child_to_wait++;
	while (i < ast->arguments.com_args.dir_args.size)
	{
		if (((t_dirargs *)ast->arguments.com_args.dir_args.data)[i].dir
			== HEREDOC)
		{
			to_close = \
		((t_dirargs *)ast->arguments.com_args.dir_args.data)[i].filename[0];
			if (close(p_mini->fds_here_doc[to_close]) < 0)
				perror("fn : parent_execution : close");
			p_mini->fds_here_doc[to_close] = -1;
		}
		i++;
	}
}
