/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:48:59 by jweber            #+#    #+#             */
/*   Updated: 2025/06/25 17:03:07 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include "ft_string.h"

static int	is_this(char **arr_to_comp, char *str);
static int	check_before(t_vector tokens, size_t i);
static int	check_after_redir(t_vector tokens, size_t i);
static int	check_after(t_vector tokens, size_t i);
static int	check_before_after(t_vector tokens, size_t i);

int	check_error_syntax(t_vector tokens)
{
	size_t	i;
	char	*smth_before[3];
	char	*smth_after[5];
	char	*smth_before_after[4];

	i = 0;
	smth_before[0] = ";";
	smth_before[1] = "&";
	smth_before[2] = NULL;
	smth_after[0] = ">";
	smth_after[1] = ">>";
	smth_after[2] = "<";
	smth_after[3] = "<<";
	smth_after[4] = NULL;
	smth_before_after[0] = "|";
	smth_before_after[1] = "||";
	smth_before_after[2] = "&&";
	smth_before_after[3] = NULL;
	while (i < tokens.size)
	{
		if (is_this(smth_before, ((char **)tokens.data)[i]) == 0)
		{
			if (check_before(tokens, i) != 0)
				return (1);
		}
		if (is_this(smth_after, ((char **)tokens.data)[i]) == 0)
		{
			if (check_after_redir(tokens, i) != 0)
				return (1);
		}
		if (is_this(smth_before_after, ((char **)tokens.data)[i]) == 0)
		{
			if (check_before_after(tokens, i) != 0)
				return (1);
		}
		i++;
	}
	return (0);
}

static int	is_this(char **arr_to_comp, char *str)
{
	size_t	i;

	i = 0;
	while (arr_to_comp[i] != NULL)
	{
		if (ft_strcmp(arr_to_comp[i], str) == 0)
			return (0);
		i++;
	}
	return (1);
}

/* should check that ((char**)token.data)[i -1]
 * is not either : "&&" "||" "|" "&" ";"
*/
static int	check_before(t_vector tokens, size_t i)
{
	char	*list_check[10];
	size_t	j;

	list_check[0] = "&&";
	list_check[1] = "&";
	list_check[2] = "||";
	list_check[3] = "|";
	list_check[4] = ";";
	list_check[5] = "<";
	list_check[6] = "<<";
	list_check[7] = ">";
	list_check[8] = ">>";
	list_check[9] = NULL;
	if (i == 0)
	{
		return (1);
	}
	else
	{
		j = 0;
		while (list_check[j] != NULL)
		{
			if (ft_strcmp(list_check[j], ((char **)tokens.data)[i - 1]) == 0)
				return (1);
			j++;
		}
	}
	return (0);
}

static int	check_after_redir(t_vector tokens, size_t i)
{
	char	*list_check[10];
	size_t	j;

	list_check[0] = "&&";
	list_check[1] = "&";
	list_check[2] = "||";
	list_check[3] = "|";
	list_check[4] = ";";
	list_check[5] = "<";
	list_check[6] = "<<";
	list_check[7] = ">";
	list_check[8] = ">>";
	list_check[9] = NULL;
	if (i == tokens.size - 1)
	{
		return (1);
	}
	else
	{
		j = 0;
		while (list_check[j] != NULL)
		{
			if (ft_strcmp(list_check[j], ((char **)tokens.data)[i + 1]) == 0)
				return (1);
			j++;
		}
	}
	return (0);
}

static int	check_before_after(t_vector tokens, size_t i)
{
	if (check_before(tokens, i) != 0)
		return (1);
	if (check_after(tokens, i) != 0)
		return (1);
	return (0);
}

static int	check_after(t_vector tokens, size_t i)
{
	char	*list_check[10];
	size_t	j;

	list_check[0] = "&&";
	list_check[1] = "&";
	list_check[2] = "||";
	list_check[3] = "|";
	list_check[4] = ";";
	list_check[5] = NULL;
	if (i == tokens.size - 1)
	{
		return (1);
	}
	else
	{
		j = 0;
		while (list_check[j] != NULL)
		{
			if (ft_strcmp(list_check[j], ((char **)tokens.data)[i + 1]) == 0)
				return (1);
			j++;
		}
	}
	return (0);
}
