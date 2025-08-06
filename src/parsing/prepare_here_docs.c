/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_here_docs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:32:44 by jweber            #+#    #+#             */
/*   Updated: 2025/07/02 16:33:39 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_vectors.h"
#include "parsing.h"
#include "ft_io.h"
#include <errno.h>
#include <readline/readline.h>

static void	init_here_doc_fds(int fds[NB_MAX_HERE_DOC]);

/* to check
 *	-> count_here_doc fail : DONE -> OK !
 *	-> get_here_doc fail : DONE -> OK !
*/
int	prepare_here_docs(t_minishell *p_mini, t_vector *p_tokens)
{
	int	ret;

	init_here_doc_fds(p_mini->fds_here_doc);
	ret = get_here_doc(p_mini, p_tokens);
	/*
	if (ret == ERROR_READ)
	{
		if (errno == EINTR)
		{
			ft_printf_fd(2, "\n");
			return (1);
		}
	}
	*/
	return (ret);
}

static void	init_here_doc_fds(int fds[NB_MAX_HERE_DOC])
{
	size_t	i;

	i = 0;
	while (i < NB_MAX_HERE_DOC)
	{
		fds[i] = -1;
		i++;
	}
	return ;
}
