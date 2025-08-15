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
#include <stdio.h>

/* to check
 *	-> dup2 fail : DONE -> OK !
*/
int	redir_here_doc(t_minishell *p_mini, t_dirargs redir)
{
	int		fd_to_chose;
	int		ret;

	fd_to_chose = redir.filename[0];
	ret = dup2(p_mini->fds_here_doc[fd_to_chose], 0);
	if (ret < 0)
	{
		perror("dup2");
		return (ERROR_DUP2);
	}
	return (0);
}
