/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:14:56 by jweber            #+#    #+#             */
/*   Updated: 2025/07/15 16:21:31 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "ast.h"
#include "execution.h"
#include <unistd.h>
#include <stdio.h>

// dont l'idée c'est de fork 
// puis dans l'enfant call exec_func sur le neoud à gauche
// et dans le parents de call exec_func sur le noeud à droite 
int	exec_subshell(t_ast *ast, t_minishell *p_mini)
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
		p_mini->last_child_id = 0;
		if (p_mini->previous_type == PIPE)
			change_fd_pipe(p_mini);
		else
		{
			if (close(p_mini->fd1[0]) == -1)
				perror("fn: exec_subshell: child left : close(p_mini->fd1[0]");
			if (close(p_mini->fd1[1]) == -1)
				perror("fn: exec_subshell: child left : close(p_mini->fd1[1]");
		}
		/*
		expand redir
		ret = change_fd_redir(p_mini, ast);
		if (ret != 0)
		{
			// do stuff ?
			// return ? 
			// should close all fds !
			//no no exit !exit(1);
			//only return here 
		}
		*/
		p_mini->previous_side = PREV_NONE;
		p_mini->previous_type = -1;
		if (pipe(p_mini->fd1) == -1)
		{
			perror("fn : run_exec : pipe(p_mini->fd1)");
			free_tree(&p_mini->head_ast);
			return (ERROR_PIPE);
		}
		p_mini->first_cmd = 1;
		ret_exec = exec_func(ast->arguments.sub_args, p_mini);
		close_fd1(p_mini);
		ret = wait_children(p_mini);
		if (ret != 0)
		{
			// to see what we do ?
			// ... no return i guess !
			;
		}
		if (close(p_mini->fd_tty_copy) < 0)
			perror("in exec_subshell : close(p_mini->fd_stdin) at start of children\n");
		exit(exit_child(p_mini, ret_exec)); // exit with ret or or ret_exec ? or with p_mini->last_child_id;
	}
	else
	{
		p_mini->last_child_id = pid;
	}
	return (0);
}
