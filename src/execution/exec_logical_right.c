/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_logical_right.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:07:43 by jweber            #+#    #+#             */
/*   Updated: 2025/08/08 14:08:48 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <execution.h>

int	exec_logical_right(t_ast *ast, t_minishell *p_mini)
{
	int	ret;

	p_mini->previous_side = PREV_RIGHT;
	ret = exec_func(ast->arguments.op_args.right, p_mini);
	if (ret != 0)
		return (ret);
	return (ret);
}
