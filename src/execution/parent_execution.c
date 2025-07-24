/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:44:07 by jweber            #+#    #+#             */
/*   Updated: 2025/07/21 14:44:21 by jweber           ###   ########.fr       */
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
	printf("in parent_execution, p_mini->last_chlid_id = %i\n", p_mini->last_child_id);
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
