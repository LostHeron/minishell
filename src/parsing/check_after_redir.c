/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_after_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:21:52 by jweber            #+#    #+#             */
/*   Updated: 2025/07/04 16:23:07 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include "ft_string.h"

static void	init_list_check_after_redir(char **list_check);

int	check_after_redir(t_vector tokens, size_t i)
{
	char	*list_check[10];
	size_t	j;

	init_list_check_after_redir(list_check);
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

static void	init_list_check_after_redir(char **list_check)
{
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
}
