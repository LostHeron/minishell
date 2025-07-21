/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:08:14 by jweber            #+#    #+#             */
/*   Updated: 2025/07/15 15:55:52 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "ast.h"
#include <unistd.h>
#include <stdio.h>

// dont l'idée c'est de fork 
// puis dans l'enfant call exec_func sur le neoud à gauche
// et dans le parents de call exec_func sur le noeud à droite 
int	exec_background(t_ast *ast, t_minishell *p_mini)
{
	int	pid;
	int	ret;
	int	ret_exec;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (ERROR_FORK);
	}
	if (pid == 0)
	{
		// est ce que c'est exec_func qu'il faut appeler ?
		// ou une fonction plus en amont ?
		// je pense exec_func c'est ok fine !
		ret_exec = exec_func(ast->arguments.op_args.left, p_mini);
		close_fd1(p_mini);
		ret = wait_children(p_mini);
		if (ret != 0)
		{
			// to see what we do ?
			// ... no return i guess !
		}
		if (close(p_mini->fd_tty_copy) < 0)
			perror("close");
		exit(exit_child(p_mini, ret)); // exit with ret or with p_mini->last_child_id;
	}
	else
	{
		// in parent : 
		p_mini->last_child_id = pid;
		ret = exec_func(ast->arguments.op_args.right, p_mini);
		/*
		if (ret != 0)
		{
			// do something else ???, I do not think so !
			return (ret);
		}
		if nothing else we can just return ret !
		*/
		return (ret);
	}
}
