/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_forking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:43:13 by jweber            #+#    #+#             */
/*   Updated: 2025/07/21 14:43:29 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "minishell.h"
#include "execution.h"
#include "printing.h"
#include "ft_string.h"
#include <readline/readline.h>
#include <unistd.h>
#include <stdio.h>

static void	child_case_forking(t_ast *ast, t_minishell *p_mini, int cmd_type);

/* to check : 
 *	-> fork fail : DONE ;
 *	-> child_execution fail : TO DO ; but what to do ?
 *	(will no change the result of main process out,
 *	because child will exit after child_execution ends);
 *		-> but we need to check that inside a child failure, everything is
 *		correctly freed !
 *	-> parent_execution fail : DONE -> OK ;
*/
int	case_forking(t_ast *ast, t_minishell *p_mini, int cmd_type)
{
	int					pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (ERROR_FORK);
	}
	if (pid == 0)
	{
		child_case_forking(ast, p_mini, cmd_type);
	}
	else
	{
		return (
			parent_execution(ast->arguments.com_args.dir_args, p_mini, pid));
	}
	return (0);
}

/* to check :
 *	-> child_execution fail : TO DO ;
*/
static void	child_case_forking(t_ast *ast, t_minishell *p_mini, int cmd_type)
{
	int	ret;

	p_mini->last_child_id = 0;
	ret = child_execution(ast, p_mini, cmd_type);
	if (ret < 0
		&& ft_strcmp(((char **)ast->arguments.com_args.content.data)[0],
		"exit") != 0)
	{
		print_error(ret);
		exit(exit_child(p_mini, 2));
	}
	exit(exit_child(p_mini, ret));
}
