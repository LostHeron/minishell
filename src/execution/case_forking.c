/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_forking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:43:13 by jweber            #+#    #+#             */
/*   Updated: 2025/07/15 16:02:30 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "minishell.h"
#include "execution.h"
#include "freeing.h"
#include <readline/readline.h>
#include <unistd.h>
#include <stdio.h>

int	case_forking(t_ast *ast, t_minishell *p_mini, int cmd_type)
{
	int	pid;
	int	ret;

	pid = fork();
	if (pid == -1)
	{
		perror("fn: case_forking: fork");
		return (ERROR_FORK);
	}
	if (pid == 0)
	{
		p_mini->last_child_id = 0;
		ret = child_execution(ast, p_mini, cmd_type);
		// here should call a function which will clear
		// all malloced ared (free_p_mini)
		// and return the correct value to return 
		// to the parent process
		exit(exit_child(p_mini, ret));
	}
	else
	{
		parent_execution(ast, p_mini, pid);
		return (0);
	}
}
