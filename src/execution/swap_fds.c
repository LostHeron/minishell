/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:26:16 by jweber            #+#    #+#             */
/*   Updated: 2025/07/15 12:01:25 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

int	swap_fds(t_minishell *p_mini)
{
	int	ret;

	ret = 0;
	if (close(p_mini->fd1[0]) != 0)
	{
		perror("swap_fds : close(p_minit->fd1[0])");
		ret = ERROR_CLOSE;
	}
	if (close(p_mini->fd1[1]) != 0)
	{
		perror("swap_fds : close(p_minit->fd1[1])");
		ret = ERROR_CLOSE;
	}
	if (ret == 0)
	{
		p_mini->fd1[0] = p_mini->fd2[0];
		p_mini->fd2[0] = -1;
		p_mini->fd1[1] = p_mini->fd2[1];
		p_mini->fd2[1] = -1;
	}
	return (ret);
}
