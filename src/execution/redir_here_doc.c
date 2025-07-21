/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:08:05 by jweber            #+#    #+#             */
/*   Updated: 2025/07/21 09:08:12 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>

int	redir_here_doc(t_minishell *p_mini, t_dirargs redir)
{
	int		fd_to_chose;

	fd_to_chose = redir.filename[0];
	if (dup2(p_mini->fds_here_doc[fd_to_chose], 0) < 0)
	{
		return (ERROR_DUP2);
	}
	return (0);
}
