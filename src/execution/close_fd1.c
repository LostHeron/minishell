/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:40:55 by jweber            #+#    #+#             */
/*   Updated: 2025/07/15 15:41:22 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

int	close_fd1(t_minishell *p_mini)
{
	int	ret;

	ret = 0;
	if (p_mini->fd1[0] != -1)
	{
		if (close(p_mini->fd1[0]) == -1)
		{
			perror("close");
			ret = ERROR_CLOSE;
		}
	}
	p_mini->fd1[0] = -1;
	if (p_mini->fd1[1] != -1)
	{
		if (close(p_mini->fd1[1]) == -1)
		{
			perror("close");
			ret = ERROR_CLOSE;
		}
	}
	p_mini->fd1[1] = -1;
	return (ret);
}
