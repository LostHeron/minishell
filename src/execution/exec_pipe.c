/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:58:00 by jweber            #+#    #+#             */
/*   Updated: 2025/07/15 13:43:12 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "ast.h"
#include <unistd.h>
#include <stdio.h>

static int	launch_left(t_ast *ast, t_minishell *p_mini);
static int	launch_right(t_ast *ast, t_minishell *p_mini);
static void	close_fd(int *p_fd);

/* to check :
 *	-> launch_left fail : DONE -> OK !
 *	-> swap_fds fail : DONE -> OK !
 *	-> launch_right fail : DONE -> OK !
*/
int	exec_pipe(t_ast *ast, t_minishell *p_mini)
{
	int	ret;

	p_mini->previous_type = PIPE;
	ret = launch_left(ast, p_mini);
	if (ret != 0)
		return (ret);
	ret = swap_fds(p_mini);
	if (ret != 0)
	{
		return (ret);
	}
	ret = launch_right(ast, p_mini);
	if (ret != 0)
		return (ret);
	return (0);
}

/* to check
 *	-> pipe fail : DONE -> OK !
 *	-> exec_func fail : DONE -> OK !
*/
static int	launch_left(t_ast *ast, t_minishell *p_mini)
{
	int	ret;

	ret = pipe(p_mini->fd2);
	if (ret < 0)
	{
		perror("pipe");
		return (ERROR_PIPE);
	}
	p_mini->previous_side = PREV_LEFT;
	ret = exec_func(ast->arguments.op_args.left, p_mini);
	if (ret != 0)
	{
		close_fd(&(p_mini->fd2[0]));
		close_fd(&(p_mini->fd2[1]));
	}
	return (ret);
}

/* to check: 
 *	-> exec_func fail : DONE -> OK !
*/
static int	launch_right(t_ast *ast, t_minishell *p_mini)
{
	int	ret;

	p_mini->previous_side = PREV_RIGHT;
	ret = exec_func(ast->arguments.op_args.right, p_mini);
	return (ret);
}

static void	close_fd(int *p_fd)
{
	if (*p_fd > 0)
	{
		if (close(*p_fd) < 0)
		{
			perror("close");
		}
		*p_fd = -1;
	}
}
