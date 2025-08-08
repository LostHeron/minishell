/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_or.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:54:30 by jweber            #+#    #+#             */
/*   Updated: 2025/08/08 14:25:17 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "minishell.h"
#include "execution.h"
#include <sys/wait.h>
#include <unistd.h>

int	exec_or(t_ast *ast, t_minishell *p_mini)
{
	int	ret;

	p_mini->previous_type = OR;
	ret = exec_logical_left(ast, p_mini);
	if (ret != 0)
		return (ret);
	if (p_mini->last_error_code != 0)
	{
		p_mini->previous_type = OR;
		ret = exec_logical_right(ast, p_mini);
		if (ret != 0)
			return (ret);
	}
	return (0);
}
