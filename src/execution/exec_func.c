/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:12:52 by jweber            #+#    #+#             */
/*   Updated: 2025/06/04 13:23:38 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "execution.h"
#include "minishell.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int	exec_func(t_ast *ast, t_minishell *p_mini)
{
	int		ret;

	if (ast->type == PIPE)
	{
		ret = exec_pipe(ast, p_mini);
		if (ret != 0)
		{
			// do stuff
			// return ?
		}
		return (0);
	}
	if (ast->type == COMMAND)
	{
		ret = exec_command(ast, p_mini);
		if (ret != 0)
		{
			// do stuff ?
			// return ?
		}
		if (p_mini->first_cmd == 1)
		{
			p_mini->first_cmd = 0;
		}
	}
	return (0);
}
