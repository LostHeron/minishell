/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:05:55 by jweber            #+#    #+#             */
/*   Updated: 2025/07/21 14:39:13 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	redir_in(char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(NULL);
		return (ERROR_OPEN);
	}
	if (dup2(fd, 0) == -1)
	{
		perror("fn: redir_in: dup2(fd, 0)");
		if (close(fd) < 0)
			perror("fn: redir_in: close(fd)");
		return (ERROR_DUP2);
	}
	if (close(fd) == -1)
	{
		perror("fn: redir_in: close(fd)");
		return (ERROR_CLOSE);
	}
	return (0);
}
