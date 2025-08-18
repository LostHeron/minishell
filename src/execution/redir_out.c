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

/* same stuff as redir_in function
 * so should behave same way 
*/
int	redir_out(char *filename)
{
	int	fd;
	int	ret;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		perror(filename);
		return (ERROR_OPEN);
	}
	ret = dup2(fd, 1);
	if (ret == -1)
	{
		perror("dup2");
		if (close(fd) < 0)
			perror("close");
		return (ERROR_DUP2);
	}
	if (close(fd) == -1)
	{
		perror("close");
		return (ERROR_CLOSE);
	}
	return (0);
}
