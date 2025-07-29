/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:07:39 by jweber            #+#    #+#             */
/*   Updated: 2025/07/21 09:07:41 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	redir_append(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd == -1)
	{
		perror(filename);
		return (ERROR_OPEN);
	}
	if (dup2(fd, 1) == -1)
	{
		perror("fn: redir_append: dup2(fd, 1)");
		if (close(fd) < 0)
			perror("fn: redir_append: close(fd)");
		return (ERROR_DUP2);
	}
	if (close(fd) == -1)
	{
		perror("fn: redir_append: close(fd)");
		return (ERROR_CLOSE);
	}
	return (0);
}
