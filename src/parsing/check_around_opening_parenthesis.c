/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_around_opening_parenthesis.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:15:28 by jweber            #+#    #+#             */
/*   Updated: 2025/07/23 17:37:24 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_vectors.h"
#include "ft_string.h"

static int	check_before_opening_parenthesis(
				t_vector *p_tokens, size_t token_i);
static int	check_after_opening_parenthesis(t_vector *p_tokens, size_t token_i);
static void	init_list_before_opening_parenthesis(char **list_check);
static void	init_list_after_opening_parenthesis(char **list_check);

/* This function is called when meeting "(" token
 *	BEFORE an opening parenthesis:
 *		it must be one of : 
 *			- nothing (opening parenthesis is the first argument)
 *			- "&&", "&", "||", "|", ";"
 *	AFTER an opening parenthesis:
 *		must have an argument 
 *		it can not be one of these tokens : ")", "&&", "&", "||", "|", ";",
 *		(but it can be ">>" or ">" or "<<" or "<" or a command)
*/
int	check_around_opening_parenthesis(t_vector *p_tokens, size_t	token_i)
{
	int	ret;

	ret = 0;
	if (token_i > 0)
		ret = check_before_opening_parenthesis(p_tokens, token_i);
	if (ret != 0)
		return (ERROR_AROUND_OPENING_PARENTHESIS);
	if (token_i == p_tokens->size - 1)
		return (ERROR_AROUND_OPENING_PARENTHESIS);
	else
		ret = check_after_opening_parenthesis(p_tokens, token_i);
	if (ret != 0)
		return (ERROR_AROUND_OPENING_PARENTHESIS);
	return (0);
}

/* this function is called when tokens is "("
 *	it is only called if token_i > 0
 *	and this function must check that p_tokens[token_i - 1]
 *	is one of "&&", "&", "||", "|", ";"
 *	return 1 (error) if it is none of previous quoted tokens
 *	return 0 if it is one of the previous quoted tokens
*/
static int	check_before_opening_parenthesis(t_vector *p_tokens, size_t token_i)
{
	char	*list_before_opening_parenthesis[6];
	size_t	list_i;

	init_list_before_opening_parenthesis(list_before_opening_parenthesis);
	list_i = 0;
	while (list_before_opening_parenthesis[list_i] != NULL)
	{
		if (ft_strcmp(list_before_opening_parenthesis[list_i],
				((char **)p_tokens->data)[token_i - 1]) == 0)
			return (0);
		list_i++;
	}
	return (1);
}

static void	init_list_before_opening_parenthesis(char **list_check)
{
	list_check[0] = "&&";
	list_check[1] = "&";
	list_check[2] = "||";
	list_check[3] = "|";
	list_check[4] = ";";
	list_check[5] = NULL;
}

/* This function is called when token is "("
 *	it will check if following tokens after "("
 *	is a valid token
 *	after a "(" the following tokens are forbiden :
 *		"&&", "&", "||", "|", ";", ")";
 *	return (0) if it is one of the previous quoted tokens
 *	return (1) if it is none of the previous quoted tokens
*/
static int	check_after_opening_parenthesis(t_vector *p_tokens, size_t token_i)
{
	char	*list_after_opening_parenthesis[7];
	size_t	list_i;

	init_list_after_opening_parenthesis(list_after_opening_parenthesis);
	list_i = 0;
	while (list_after_opening_parenthesis[list_i] != NULL)
	{
		if (ft_strcmp(list_after_opening_parenthesis[list_i],
				((char **)p_tokens->data)[token_i + 1]) == 0)
			return (1);
		list_i++;
	}
	return (0);
}

static void	init_list_after_opening_parenthesis(char **list_check)
{
	list_check[0] = "&&";
	list_check[1] = "&";
	list_check[2] = "||";
	list_check[3] = "|";
	list_check[4] = ";";
	list_check[5] = ")";
	list_check[6] = NULL;
}
