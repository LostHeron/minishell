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

static void	init_here_doc_fds(int fds[NB_MAX_HERE_DOC]);

int	prepare_here_doc(t_minishell *p_mini, t_vector *p_tokens)
{
	int	ret;

	init_here_doc_fds(p_mini->fds_here_doc);
	ret = count_here_doc(*p_tokens);
	if (ret != 0)
	{
		ft_putstr_fd("maximum here-document count exceeded\n", 2);
		p_mini->last_error_code = 2;
		return (0);
	}
	ret = get_here_doc(p_mini, p_tokens);
	if (ret != 0)
	{
		ft_putstr_fd("problem occured in function 'get_here_doc'\n", 2);
		return (0);
	}
	return (0);
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
