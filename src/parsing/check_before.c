/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_before.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:22:37 by jweber            #+#    #+#             */
/*   Updated: 2025/07/04 16:23:03 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include "ft_string.h"

static void	init_list_check_before(char **list_check);

/* This function is called when token is one of : ";" "&"
 * should check that ((char**)token.data)[i -1]
 * exists (meaning i != 0) and is not one of : "(" "&&" "||" "|" "&" ";"
 * we also checks that it is not '>' '>>' '<<' or '<' but this 
 * check should be checked in function check_after
 * 
 * if it is ok : return 0
 * if it is bad token : return 1
*/
int	check_before(t_vector tokens, size_t i)
{
	char	*list_check[11];
	size_t	j;

	init_list_check_before(list_check);
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

static void	init_list_check_before(char **list_check)
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
	list_check[9] = "(";
	list_check[10] = NULL;
}
