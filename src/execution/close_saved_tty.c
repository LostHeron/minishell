/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_saved_tty.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:51:13 by jweber            #+#    #+#             */
/*   Updated: 2025/07/30 13:00:05 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include <stdio.h>
#include <unistd.h>

static void	close_fd(int *p_fd, int *p_final_ret);

/* to check
 *	-> first close_fd fail : DONE -> OK !
 *	-> second close_fd fail : DONE -> OK !
 *	-> third close_fd fail : DONE -> OK !
*/
int	close_saved_tty(t_minishell *p_mini)
{
	int	final_ret;

	final_ret = 0;
	close_fd(&(p_mini->fd_tty_in), &final_ret);
	close_fd(&(p_mini->fd_tty_out), &final_ret);
	close_fd(&(p_mini->fd_tty_err), &final_ret);
	return (final_ret);
}

/* to check
 *	-> close fail : DONE -> OK !
*/
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
