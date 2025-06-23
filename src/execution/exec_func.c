/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:12:52 by jweber            #+#    #+#             */
/*   Updated: 2025/06/23 13:09:40 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "execution.h"
#include "minishell.h"
#include "ft_io.h"
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
	else if (ast->type == COMMAND)
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
	else if (ast->type == AND)
	{
		ret = exec_and(ast, p_mini);
		if (ret != 0)
		{
			// do stuff ?
			return (ret);
		}
	}
	else if (ast->type == OR)
	{
		ret = exec_or(ast, p_mini);
		{
			// do stuff ?
			return (ret);
		}
	}
	else
	{
		ft_putstr_fd("ERROR : ast-type not defined !\n", 2);
		ft_putstr_fd("EXITING program !\n", 2);
		exit(1);
	}
	return (0);
}
