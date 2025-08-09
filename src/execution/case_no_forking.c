/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_no_forking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:45:10 by jweber            #+#    #+#             */
/*   Updated: 2025/07/18 11:15:33 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"
#include "execution.h"
#include "ft_io.h"

/* this function is called when trying to exec a builtin or a command
 * which contains only redirections
 * it should : 
 *	- perform redirections !
 *	- then execute the correspongind builtin if command is not empty !
 *		-> if builtin function return 0 : execution succeed !
 *		-> if builtin function return positive value, error inside builtin 
 *		but must continue 
 *		-> if builtin function return negative value, error inside builtin
 *		that must make us stop execution of the program 
 *	- then restore fd to its original !
 *	to check : 
 *	-> 
*/
int	case_no_forking(t_ast *ast, t_minishell *p_mini)
{
	int	ret_builtin;
	int	ret;

	ret = 0;
	p_mini->last_child_id = 0;
	ret = change_fd_redir(p_mini, ast->arguments.com_args.dir_args);
	if (ret != 0)
	{
		if (ret == ERROR_OPEN)
		{
			ret = restore_fds(p_mini);
			if (ret != 0)
			{
				ft_putstr_fd(
					"could not restore fds, stopping programme execution\n",
					p_mini->fd_tty_err);
				return (-10);
			}
			p_mini->last_error_code = 1;
		}
		return (ret);
	}
	if (((char **)ast->arguments.com_args.content.data)[0] != NULL)
	{
		ret_builtin = call_builtins(p_mini, ast->arguments.com_args.content);
		if (ret_builtin >= 0)
			p_mini->last_error_code = ret_builtin;
		else
			p_mini->last_error_code = 2;
	}
	else
	{
		ret_builtin = ret;
		p_mini->last_error_code = ret;
	}
	ret = restore_fds(p_mini);
	if (ret != 0)
	{
		ft_putstr_fd(
			"could not restore fds, stopping programme execution\n",
			p_mini->fd_tty_err);
		return (-10);
	}
	if (ret_builtin < 0)
		return (ret_builtin);
	return (0);
}
