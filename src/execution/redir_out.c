/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:06:53 by jweber            #+#    #+#             */
/*   Updated: 2025/07/21 14:39:19 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	redir_out(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		perror(NULL);
		return (ERROR_OPEN);
	}
	if (dup2(fd, 1) == -1)
	{
		perror("fn: redir_out: dup2(fd, 1)");
		if (close(fd) < 0)
			perror("fn: redire_out: close(fd)");
		return (ERROR_DUP2);
	}
	if (close(fd) == -1)
	{
		perror("fn: redir_out: close(fd)");
		return (ERROR_CLOSE);
	}
	return (0);
}
