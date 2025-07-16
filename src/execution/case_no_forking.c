/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_no_forking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:45:10 by jweber            #+#    #+#             */
/*   Updated: 2025/07/15 11:58:01 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"
#include "execution.h"
#include "ft_io.h"

int	case_no_forking(t_ast *ast, t_minishell *p_mini)
{
	int	ret_builtin;
	int	ret;

	p_mini->last_child_id = 0;
	ret = change_fd_redir(p_mini, ast);
	if (ret != 0)
		return (ret);
	ret_builtin = call_builtins(p_mini, ast->arguments.com_args.content);
	p_mini->last_error_code = ret_builtin;
	ret = restore_fds(p_mini);
	if (ret != 0)
	{
		ft_putstr_fd("could not restore fds, stopping programme execution\n", 2);
		return (-1);
	}
	if (ret_builtin < 0)
		return (ret_builtin);
	return (0);
}
