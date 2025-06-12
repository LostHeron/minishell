/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:02:34 by jweber            #+#    #+#             */
/*   Updated: 2025/06/04 14:14:23 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

int	exec_command(t_ast *ast, t_minishell *p_mini)
{
	int		pid;
	int		ret;

	/*
	if (p_mini->previous_type == PIPE)
		change_fd_pipe(p_mini);
	*/
	pid = fork();
	if (pid == -1)
	{
		// see later !
		// return ??
		;
	}
	if (pid == 0)
	{
		ret = child_execution(ast, p_mini);
		if (ret != 0)
		{
			// do stuff;
			// return (ret); ?
		}
	}
	else
	{
		// in parent !
		// do something here ??? je crois pas 
	}
	return (0);
}
