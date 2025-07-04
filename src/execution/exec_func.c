/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:27:28 by jweber            #+#    #+#             */
/*   Updated: 2025/07/04 18:28:21 by jweber           ###   ########.fr       */
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

int	exec_func(t_ast *ast, t_minishell *p_mini)
{
	int		ret;
	int		(*exec_table[NB_T_TYPE])(t_ast *ast, t_minishell *p_mini);

	init_exec_table(exec_table);
	if (0 <= ast->type && ast->type <= 7)
	{
		ret = exec_table[ast->type](ast, p_mini);
		if (ret != 0)
		{
			return (ret);
		}
	}
	else
	{
		ft_putstr_fd("ERROR : ast-type not defined !\n", 2);
		ft_putstr_fd("EXITING program !\n", 2);
		p_mini->should_exit = TRUE;
		p_mini->last_error_code = 1;
		return (1);
	}
	return (0);
}

static void	init_exec_table(int (*exec_table[NB_T_TYPE])(t_ast *ast, \
														t_minishell *p_mini))
{
	exec_table[OR] = &exec_or;
	exec_table[AND] = &exec_and;
	exec_table[COMMAND] = &exec_command;
	exec_table[PIPE] = &exec_pipe;
	//exec_func[BACKGROUND] = &exec_background;
	//exec_func[SEQUENCE] = &exec_sequence;
	//exec_func[SUBSHELL] = &exec_subshell;
	return ;
}
