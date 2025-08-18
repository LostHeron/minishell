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

static void	close_fd(int *p_fd, int *p_final_ret);

/* to check
 *	-> first close fail : DONE -> OK !
 *	-> second close fail :  DONE -> OK !
*/
int	close_case_no_pipe(t_minishell *p_mini)
{
	int	ret;

	ret = 0;
	close_fd(&(p_mini->fd1[0]), &ret);
	close_fd(&(p_mini->fd1[1]), &ret);
	return (ret);
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
			*p_final_ret = ERROR_CLOSE;
		}
		*p_fd = -1;
	}
}
