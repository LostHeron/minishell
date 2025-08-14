/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:43:35 by jweber            #+#    #+#             */
/*   Updated: 2025/08/05 14:19:57 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include "minishell.h"
#include "execution.h"
#include <unistd.h>

/*		This function is called by exec_func->exec_command->case_forking->
 * ->child_execution->make_redirections
 *
 *		This function should perform redirection, starting 
 *	with pipe redirection using the fd1 and fd2 opened pipe !
 *	the it should close those file descriptor after having them dup2, 
 *	the following fd should be then closed :
 *		- p_mini->fd1[0];
 *		- p_mini->fd1[1];
 *		if it has been opened : 
 *			- p_mini->fd2[0];
 *			- p_mini->fd2[1];
 *		and all here_doc fds opened previously 
 *
 *		Then the function should perform < << > >> redirections
 *	and close the fd opened after each performed redirection.
 * to check : 
 *	-> change_fd_pipe fail : DONE -> OK !
 *	-> close_case_no_pipe fail : DONE -> OK!
 *	-> change_fd_redir : TO DO ;
*/
int	make_redirections(t_vector redir, t_minishell *p_mini)
{
	int	ret;

	if (p_mini->previous_type == PIPE)
	{
		ret = change_fd_pipe(p_mini);
		if (ret != 0)
		{
			close_here_doc_fds(p_mini);
			return (ret);
		}
	}
	else
	{
		ret = close_case_no_pipe(p_mini);
		if (ret != 0)
		{
			close_here_doc_fds(p_mini);
			return (ret);
		}
	}
	ret = change_fd_redir(p_mini, redir);
	return (ret);
}
