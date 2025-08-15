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

#include "ft_vectors.h"
#include "minishell.h"
#include "execution.h"
#include "ft_io.h"
#include "ft_string.h"

static void	presence_of_commands(t_vector args, t_minishell *p_mini,
				int *p_ret, int *p_ret_builtin);
static int	case_change_fd_redir_fail(t_minishell *p_mini, int ret);

/* this function is called when trying to exec a builtin or a command
 * which contains only redirections
 * it should : 
 *	- perform redirections !
 *		-> stop if one redirection fails and return without executing the command
 *	- then execute the correspongind builtin if command is not empty !
 *		-> if builtin function return 0 : execution succeed !
 *		-> if builtin function return positive value, error inside builtin 
 *		but must continue 
 *		-> if builtin function return negative value, error inside builtin
 *		that must make us stop execution of the program 
 *	- then restore fd to its original !
 *	to check : 
 *	-> change_fd_redir fail : TO DO ;
*/
int	case_no_forking(t_vector args, t_vector redir, t_minishell *p_mini)
{
	int	ret_builtin;
	int	ret;

	ret = 0;
	p_mini->last_child_id = 0;
	ret = change_fd_redir(p_mini, redir);
	if (ret != 0)
		return (case_change_fd_redir_fail(p_mini, ret));
	presence_of_commands(args, p_mini, &ret, &ret_builtin);
	ret = restore_fds(p_mini);
	if (ret != 0)
	{
		ft_putstr_fd(
			"could not restore fds, stopping programme execution\n",
			p_mini->fd_tty_err);
		p_mini->should_exit = TRUE;
		return (-100);
	}
	if (ret_builtin < 0 && ft_strcmp(((char **)args.data)[0],
		"exit") != 0)
		return (ret_builtin);
	return (0);
}

static void	presence_of_commands(t_vector args, t_minishell *p_mini,
						int *p_ret, int *p_ret_builtin)
{
	if (((char **)args.data)[0] != NULL)
	{
		*p_ret_builtin = call_builtins(p_mini, args);
		if (*p_ret_builtin >= 0
			|| ft_strcmp(((char **)args.data)[0], "exit") == 0)
			p_mini->last_error_code = *p_ret_builtin;
		else
			p_mini->last_error_code = 2;
	}
	else
	{
		*p_ret_builtin = *p_ret;
		p_mini->last_error_code = *p_ret;
	}
}

static int	case_change_fd_redir_fail(t_minishell *p_mini, int ret)
{
	int	tmp_ret;

	if (ret == ERROR_OPEN)
	{
		p_mini->last_error_code = 1;
	}
	tmp_ret = restore_fds(p_mini);
	if (tmp_ret != 0)
	{
		ft_putstr_fd(
			"could not restore fds, stopping programme execution\n",
			p_mini->fd_tty_err);
		p_mini->should_exit = TRUE;
		return (-100);
	}
	return (ret);
}
