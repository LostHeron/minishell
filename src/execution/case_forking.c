/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_forking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:43:13 by jweber            #+#    #+#             */
/*   Updated: 2025/07/04 18:47:30 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "minishell.h"
#include "execution.h"
#include <unistd.h>
#include <stdio.h>

int	case_forking(t_ast *ast, t_minishell *p_mini, int cmd_type)
{
	int	pid;
	int	ret;

	pid = fork();
	if (pid == -1)
	{
		perror("fn: ... : fork");
		return (ERROR_FORK);
	}
	if (pid == 0)
	{
		p_mini->should_exit = TRUE;
		ret = child_execution(ast, p_mini, cmd_type);
		return (ret);
	}
	else
	{
		parent_execution(ast, p_mini, pid);
		return (0);
	}
}
