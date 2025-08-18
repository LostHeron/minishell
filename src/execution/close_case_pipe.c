/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_case_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:21:08 by jweber            #+#    #+#             */
/*   Updated: 2025/08/07 15:17:13 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

static void	close_fd(int *p_fd, int *p_final_ret);

/* to check
 * -> first close_fd fail : DONE -> OK;
 * -> second close_fd fail : DONE -> OK;
 * -> third close_fd fail : DONE -> OK;
 * -> forth close_fd fail : DONE -> OK;
*/
int	close_case_pipe(t_minishell *p_mini, int final_ret)
{
	close_fd(&(p_mini->fd1[0]), &final_ret);
	close_fd(&(p_mini->fd1[1]), &final_ret);
	close_fd(&(p_mini->fd2[0]), &final_ret);
	close_fd(&(p_mini->fd2[1]), &final_ret);
	return (final_ret);
}

static void	close_fd(int *p_fd, int *p_final_ret)
{
	int	ret;

	if (*p_fd > 0)
	{
		ret = close(*p_fd);
		if (ret < 0)
		{
			perror("close");
			if (*p_final_ret == 0)
				*p_final_ret = ERROR_CLOSE;
		}
		*p_fd = -1;
	}
}
