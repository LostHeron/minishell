/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_fd_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:44:39 by jweber            #+#    #+#             */
/*   Updated: 2025/07/21 11:00:04 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "ft_vectors.h"
#include "minishell.h"
#include "execution.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

static void	init_redir_table(int (*redir_table[3])(char *filename));
static int	perform_redir_i(t_minishell *p_mini, t_dirargs redir,
				int (*redir_table[3])(char *filename));
/*
static int	redir_heredoc(t_ast *ast, size_t i);
*/

/* this function should handle the following redirction :
 *  - <<
 *  - >>
 *  - >
 *  - <
 *  it should also ensure after the function return that all heredocuments fd 
 *  are closed !
 *  in case of success:
 *		return (0);
 *	in case of failure:
 *		return error_code associated with failure and do not perform
 *		the following redir
 *
 * to check :
 *	-> perform_redir_i fail : DONE -> OK !
*/
int	change_fd_redir(t_minishell *p_mini, t_vector redir)
{
	size_t	i;
	int		ret;
	int		(*redir_table[3])(char *filename);

	i = 0;
	init_redir_table(redir_table);
	ret = 0;
	while (i < redir.size)
	{
		ret = perform_redir_i(p_mini,
				((t_dirargs *)redir.data)[i], redir_table);
		if (ret != 0)
		{
			return (ret);
		}
		i++;
	}
	return (ret);
}

/* to check :
 *	-> redir_table fail : DONE -> OK !
 *		-> redir_in fail : DONE -> OK !
 *		-> redir_out fail : DONE -> OK !
 *		-> redir_append fail : DONE -> OK !
 *	-> redir_here_doc fail : DONE -> OK !
*/
static int	perform_redir_i(t_minishell *p_mini, t_dirargs redir,
			int (*redir_table[3])(char *filename))
{
	int	ret;

	if (IN <= redir.dir && redir.dir <= APPEND)
	{
		ret = redir_table[redir.dir](redir.filename);
		if (ret != 0)
			return (ret);
	}
	else if (redir.dir == HEREDOC)
	{
		ret = redir_here_doc(p_mini, redir);
		if (ret != 0)
			return (ret);
	}
	return (0);
}

static void	init_redir_table(int (*redir_table[3])(char *filename))
{
	redir_table[IN] = &redir_in;
	redir_table[OUT] = &redir_out;
	redir_table[APPEND] = &redir_append;
}
