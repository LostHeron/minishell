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

static void	close_fd(int *p_fd, int *p_ret);

/* to check
 *	-> close_fail : DONE -> OK ! (forgot to close fd2 in case 
 *	close on fd1 failed)
*/
int	swap_fds(t_minishell *p_mini)
{
	int	ret;

	ret = 0;
	close_fd(&(p_mini->fd1[0]), &ret);
	close_fd(&(p_mini->fd1[1]), &ret);
	if (ret == 0)
	{
		p_mini->fd1[0] = p_mini->fd2[0];
		p_mini->fd2[0] = -1;
		p_mini->fd1[1] = p_mini->fd2[1];
		p_mini->fd2[1] = -1;
	}
	else
	{
		close_fd(&(p_mini->fd2[0]), &ret);
		close_fd(&(p_mini->fd2[1]), &ret);
	}
	return (ret);
}

static void	close_fd(int *p_fd, int *p_ret)
{
	int	ret;

	if (*p_fd > 0)
	{
		ret = close(*p_fd);
		if (ret < 0)
		{
			perror("close");
			*p_ret = ERROR_CLOSE;
		}
		*p_fd = -1;
	}
}
