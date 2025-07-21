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

void	close_fd1(t_minishell *p_mini)
{
	if (p_mini->fd1[0] != -1)
		if (close(p_mini->fd1[0]) == -1)
			perror("fn: close_fd1: (close(minishell.fd1[0])");
	p_mini->fd1[0] = -1;
	if (p_mini->fd1[1] != -1)
		if (close(p_mini->fd1[1]) == -1)
			perror("fn: close_fd1: (close(minishell.fd1[1])");
	p_mini->fd1[1] = -1;
}
