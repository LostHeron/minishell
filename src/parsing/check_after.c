/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_after.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:24:15 by jweber            #+#    #+#             */
/*   Updated: 2025/07/04 16:25:04 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include "ft_string.h"

int	check_after(t_vector tokens, size_t i)
{
	char	*list_check[10];
	size_t	j;

	list_check[0] = "&&";
	list_check[1] = "&";
	list_check[2] = "||";
	list_check[3] = "|";
	list_check[4] = ";";
	list_check[5] = ")";
	list_check[6] = NULL;
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
