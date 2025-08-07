/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:00:16 by jweber            #+#    #+#             */
/*   Updated: 2025/08/06 14:55:20 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_vectors.h"
#include "check_errors.h"
#include "ft_io.h"

static int	check_here_doc_count(t_minishell *p_mini, t_vector *p_tokens);

/* This function should check that there is no syntax
 * errors. It will return 0 if no syntax error are present
 * and one in the other case.
 * It will also read all heredocuments
 * to check:
 *  -> check error_syntax fail         : DONE -> OK !
 *  -> check matching_parenthesis fail : DONE -> OK !
 *  -> check around_parenthesis fail   : DONE -> OK !
 *  -> check prepare_here_doc fail     : DONE -> OK !
*/
int	check_errors(t_minishell *p_mini, t_vector *p_tokens)
{
	int	ret;

	ret = check_error_syntax(*p_tokens);
	if (ret != 0)
		return (ret);
	ret = check_matching_parenthesis(p_tokens);
	if (ret != 0)
		return (ret);
	ret = check_around_parenthesis(p_tokens);
	if (ret != 0)
		return (ret);
	ret = check_here_doc_count(p_mini, p_tokens);
	if (ret != 0)
		return (ret);
	/*
	ret = prepare_here_docs(p_mini, p_tokens);
	if (ret != 0)
		return (ret);
	*/
	return (0);
}

static int	check_here_doc_count(t_minishell *p_mini, t_vector *p_tokens)
{
	int	ret;

	ret = count_here_doc(*p_tokens);
	if (ret != 0)
	{
		ft_putstr_fd("maximum here-document count exceeded\n", 2);
		p_mini->last_error_code = 2;
		return (1);
	}
	return (0);
}
