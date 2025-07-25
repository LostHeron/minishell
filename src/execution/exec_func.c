/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:27:28 by jweber            #+#    #+#             */
/*   Updated: 2025/07/21 14:43:56 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "execution.h"
#include "minishell.h"
#include "ft_io.h"
#include <unistd.h>
#include <fcntl.h>

static void	init_exec_table(int (*exec_table[NB_T_TYPE])(t_ast *ast, \
														t_minishell *p_mini));

/*	This function is the entry point for executing command 
 *	it uses the data structure ast to know how to execute commands 
 *	if it encounters an error in the call of the next function,
 *	the error must be returned
 *	in case of error the execution of the rest of the line is
 *	not performed
 *	if the error is positive :
 *		the user should be given a message indicating the error
 *		and give the prompt back to ask for more commands
 *	if the error is negative :
 *		the user must be given a message indicating the error
 *		but the prompt must not be given back and the shell should exit !
	*/
int	exec_func(t_ast *ast, t_minishell *p_mini)
{
	int		(*exec_table[NB_T_TYPE])(t_ast *ast, t_minishell *p_mini);

	init_exec_table(exec_table);
	if (0 <= ast->type && ast->type <= 6)
	{
		return (exec_table[ast->type](ast, p_mini));
	}
	else
	{
		ft_putstr_fd("ERROR : ast-type not defined !\n", 2);
		ft_putstr_fd("EXITING program !\n", 2);
		print_tree(ast, 0); // should print the tree on stderr !
		p_mini->should_exit = TRUE;
		p_mini->last_error_code = 1;
		return (1);
	}
}

static void	init_exec_table(int (*exec_table[NB_T_TYPE])(t_ast *ast, \
														t_minishell *p_mini))
{
	exec_table[OR] = &exec_or;
	exec_table[AND] = &exec_and;
	exec_table[COMMAND] = &exec_command;
	exec_table[PIPE] = &exec_pipe;
	exec_table[BACKGROUND] = &exec_background;
	exec_table[SEQUENCE] = &exec_sequence;
	exec_table[SUBSHELL] = &exec_subshell;
	return ;
}
