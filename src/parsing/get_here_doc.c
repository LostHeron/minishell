/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:16:57 by jweber            #+#    #+#             */
/*   Updated: 2025/07/14 16:58:44 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_standard.h"
#include "ft_string.h"
#include "ft_vectors.h"
#include "minishell.h"
#include "parsing.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

static int	get_here_doc_i(t_minishell *p_mini, t_vector *p_tokens, int i,	\
															int *p_hd_count);
static int	close_all_here_doc(t_minishell *p_mini);

/* main function of here_doc
 * if an error occurs when calling get_here_doc_i,
 * the function should then free / close everything related to 
 * heredoc and return an error corresponding to the problem
 * to check : 
 *	-> get_here_doc_i fail : TO DO ;
 *	-> close_all_here_doc fail : TO DO ;
*/
int	get_here_doc(t_minishell *p_mini, t_vector *p_tokens)
{
	size_t	i;
	int		ret;
	int		hd_count;

	i = 0;
	hd_count = 0;
	while (i < p_tokens->size)
	{
		ret = get_here_doc_i(p_mini, p_tokens, i, &hd_count);
		if (ret != 0)
		{
			if (close_all_here_doc(p_mini) != 0)
				return (ERROR_CLOSE);
			return (ret);
		}
		i++;
	}
	return (0);
}

/* This function will handle one here_document
 * to check
 *	-> write_to_here_doc fail : TO DO ;
 *	-> ft_malloc faile : TO DO ;
*/
static int	get_here_doc_i(t_minishell *p_mini, t_vector *p_tokens, int i,	\
													int *p_hd_count)
{
	int	ret;

	if (ft_strcmp(((char **)p_tokens->data)[i], "<<") == 0)
	{
		ret = write_to_here_doc(p_mini, p_tokens, i, p_hd_count);
		if (ret != 0)
			return (ret);
		free(((char **)p_tokens->data)[i + 1]);
		((char **)p_tokens->data)[i + 1] = ft_malloc(2 * sizeof(char));
		if (((char **)p_tokens->data)[i + 1] == NULL)
		{
			// do other stuff ?
			return (ERROR_MALLOC);
		}
		((char **)p_tokens->data)[i + 1][0] = *p_hd_count;
		((char **)p_tokens->data)[i + 1][1] = '\0';
		(*p_hd_count)++;
	}
	return (0);
}

static int	close_all_here_doc(t_minishell *p_mini)
{
	size_t	i;
	int		final_ret;

	i = 0;
	final_ret = 0;
	while (i < NB_MAX_HERE_DOC)
	{
		if (p_mini->fds_here_doc[i] != -1)
		{
			if (close(p_mini->fds_here_doc[i]) < 0)
			{
				perror("fn: close_all_here_doc: close");
				final_ret = ERROR_CLOSE;
			}
		}
		i++;
	}
	return (final_ret);
}
