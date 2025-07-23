/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:00:16 by jweber            #+#    #+#             */
/*   Updated: 2025/07/23 14:52:58 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_vectors.h"
#include "parsing.h"
#include "ft_io.h"
#include "printing.h"

int	check_errors(t_minishell *p_mini, t_vector *p_tokens)
{
	int	ret;

	ret = check_error_syntax(*p_tokens);
	if (ret != 0)
	{
		ft_putstr_fd("error syntax in check_error_syntax !\n", 2); // change this error message
		// to display a nicer message of type error synthax in pipe '|' pipe cannot be followed by 
		// ... ...
		// and must be done at start of function 
		return (ret);
	}
	ret = check_matching_parenthesis(p_tokens);
	if (ret != 0)
		return (ret);
	/*
	ret = check_around_parenthesis(p_tokens);
	if (ret != 0)
		return (ret);
	*/
	ret = prepare_here_doc(p_mini, p_tokens);
	if (ret != 0)
		return (ret);
	return (0);
}

/*
static int check_around_parenthesis(t_tokens *p_tokens)
{

}
*/
