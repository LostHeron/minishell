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
#include <readline/readline.h>
#include <unistd.h>
#include <stdio.h>

/* to check : 
 *	-> fork fail : DONE ;
 *	-> child_execution fail : TO DO ; but what to do ?
 *	(will no change the result of main process out,
 *	because child will exit after child_execution ends);
 *	-> parent_execution fail : DONE -> OK ;
*/
int	case_forking(t_ast *ast, t_minishell *p_mini, int cmd_type)
{
	int					pid;
	int					ret;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (ERROR_FORK);
	}
	if (pid == 0)
	{
		p_mini->last_child_id = 0;
		ret = child_execution(ast, p_mini, cmd_type);
		if (ret < 0)
		{
			print_error(ret);
			exit(exit_child(p_mini, 2));
		}
		exit(exit_child(p_mini, ret));
	}
	else
	{
		return (
			parent_execution(ast->arguments.com_args.dir_args, p_mini, pid));
	}
}
