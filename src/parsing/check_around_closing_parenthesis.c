/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_around_closing_parenthesis.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:38:45 by jweber            #+#    #+#             */
/*   Updated: 2025/07/24 13:37:44 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_vectors.h"
#include "ft_string.h"

static int	check_before_closing_parenthesis(
				t_vector *p_tokens, size_t token_i);
static void	init_list_before_closing_parenthesis(char **list_check);
int			check_after_closing_parenthesis(t_vector *p_tokens, size_t token_i);

int	check_around_closing_parenthesis(t_vector *p_tokens, size_t	token_i)
{
	int	ret;

	ret = 0;
	if (token_i > 0)
		ret = check_before_closing_parenthesis(p_tokens, token_i);
	if (ret != 0)
		return (ERROR_AROUND_CLOSING_PARENTHESIS);
	if (token_i == 0)
		return (ERROR_AROUND_CLOSING_PARENTHESIS);
	else
		ret = check_after_closing_parenthesis(p_tokens, token_i);
	if (ret != 0)
		return (ERROR_AROUND_CLOSING_PARENTHESIS);
	return (0);
}

/* Function will check if parameters before a closing parenthesis are ok :
 *	following tokens are FORBIDDEN before a closing parenthesis: 
 *		- "&&", "||", "|", "(", ">", ">>", "<", "<<"
 *	but those one are ALLOWED :
 *		- "&", ";"
 *	return 1 if token_i - 1 is one of forbidden token
 *	return 0 if token_i - 1 is none of forbidden token
*/
static int	check_before_closing_parenthesis(t_vector *p_tokens, size_t token_i)
{
	char	*list_before_closing_parenthesis[9];
	size_t	list_i;

	init_list_before_closing_parenthesis(list_before_closing_parenthesis);
	list_i = 0;
	while (list_before_closing_parenthesis[list_i] != NULL)
	{
		if (ft_strcmp(list_before_closing_parenthesis[list_i],
				((char **)p_tokens->data)[token_i - 1]) == 0)
			return (1);
		list_i++;
	}
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
