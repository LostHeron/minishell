/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_after_closing_parenthesis.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:37:03 by jweber            #+#    #+#             */
/*   Updated: 2025/07/24 13:39:03 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include "ft_string.h"

static void	init_list_after_closing_parenthesis(char **list_check);
static void	skip_redir_after_closing_parenthesis(
				t_vector *p_tokens, size_t	*p_token_i_after_redir);
static int	is_redir(char *token);
static void	init_list_redir(char **list_redir);

/* this function check parameters after a closing parenthesis
 * after a closing parenthesis, 
 * there can be multiple redirections meaning : 
 *	a "<" or "<<" or ">" or ">>" followed by a word
 *	but, after those redirection
 *	there must be nothing (token_i == p_tokens.size - 1)
 *	or the token must be one of :
 *		"&&" "&" ";" "||" "|";
*/
int	check_after_closing_parenthesis(t_vector *p_tokens, size_t token_i)
{
	char	*list_after_closing_parenthesis[9];
	size_t	list_i;
	size_t	token_i_after_redir;

	token_i_after_redir = token_i + 1;
	skip_redir_after_closing_parenthesis(p_tokens, &token_i_after_redir);
	init_list_after_closing_parenthesis(list_after_closing_parenthesis);
	if (token_i_after_redir == p_tokens->size)
		return (0);
	else
	{
		list_i = 0;
		while (list_after_closing_parenthesis[list_i] != NULL)
		{
			if (ft_strcmp(((char **)p_tokens->data)[token_i_after_redir],
				list_after_closing_parenthesis[list_i]) == 0)
				return (0);
			list_i++;
		}
	}
	return (1);
}

static void	init_list_after_closing_parenthesis(char **list_check)
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

static void	skip_redir_after_closing_parenthesis(
	t_vector *p_tokens, size_t	*p_token_i_after_redir)
{
	while (*p_token_i_after_redir < p_tokens->size
		&& is_redir(((char **)p_tokens->data)[*p_token_i_after_redir]) == 0)
	{
		*p_token_i_after_redir += 2;
	}
	return ;
}

/* function checks if the current token is one of :
 * "<" "<<" ">" ">>"
 *	return 0 if it is one of the previous quoted token
 *	return 1 if it is none of the previous token 
*/
static int	is_redir(char *token)
{
	char	*list_redir[5];
	size_t	list_i;

	init_list_redir(list_redir);
	list_i = 0;
	while (list_redir[list_i] != NULL)
	{
		if (ft_strcmp(token, list_redir[list_i]) == 0)
			return (0);
		list_i++;
	}
	return (1);
}

static void	init_list_redir(char **list_redir)
{
	list_redir[0] = ">";
	list_redir[1] = ">>";
	list_redir[2] = "<";
	list_redir[3] = "<<";
	list_redir[4] = NULL;
}
