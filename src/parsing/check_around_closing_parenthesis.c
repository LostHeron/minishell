/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_around_closing_parenthesis.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:38:45 by jweber            #+#    #+#             */
/*   Updated: 2025/07/23 17:46:40 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"

static int	check_before_closing_parenthesis(
				t_vector *p_tokens, size_t token_i);
static int	check_after_closing_parenthesis(t_vector *p_tokens, size_t token_i);
static void	init_list_before_closing_parenthesis(char **list_check);
static void	init_list_after_closing_parenthesis(char **list_check);

int	check_around_closing_parenthesis(t_vector *p_tokens, size_t	token_i)
{
	int	ret;

	ret = 0;
	if (token_i > 0)
		ret = check_before_closing_parenthesis(p_tokens, token_i);
	if (ret != 0)
		return (ret);
	if (token_i == p_tokens->size -1)
		return (1);
	else
		ret = check_after_closing_parenthesis(p_tokens, token_i);
	return (ret);
}

/* Function will check if parameters before a closing parenthesis are ok :
 *	following tokens are FORBIDDEN before a closing parenthesis: 
 *		- "&&", "||", "|", "(", ">", ">>", "<", "<<"
 *	but those one are ALLOWED :
 *		- "&", ";"
*/
static int	check_before_closing_parenthesis(t_vector *p_tokens, size_t token_i)
{
	return (0);
}


static void	init_list_before_closing_parenthesis(char **list_check)
{
	list_check[0] = "&&";
	list_check[1] = "||";
	list_check[2] = "|";
	list_check[3] = ">";
	list_check[4] = ">>";
	list_check[5] = "<";
	list_check[6] = "<<";
	list_check[7] = "(";
	list_check[8] = NULL;
}
