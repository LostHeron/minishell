/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_case_no_pipe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:54:58 by jweber            #+#    #+#             */
/*   Updated: 2025/07/21 14:57:43 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

int	close_case_no_pipe(t_minishell *p_mini)
{
	int	ret;

	ret = 0;
	if (close(p_mini->fd1[0]) == -1)
	{
		perror("fn: child_execution: child left: close(p_mini->fd1[0]");
		ret = ERROR_CLOSE;
	}
	if (close(p_mini->fd1[1]) == -1)
	{
		perror("fn: child_execution: child left: close(p_mini->fd1[1]");
		ret = ERROR_CLOSE;
	}
	return (ret);
}
