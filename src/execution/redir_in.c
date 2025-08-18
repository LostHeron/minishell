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

/* to check 
 *	-> open fail : DONE -> OK !
 *	-> dup2 fail : DONE -> OK !
 *	-> close -> not checking cuz closing the fd opened just before
 *	so Do no see the case in which it can fail -> but should be ok !
*/
int	redir_in(char *filename)
{
	int		fd;
	int		ret;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(filename);
		return (ERROR_OPEN);
	}
	ret = dup2(fd, 0);
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
