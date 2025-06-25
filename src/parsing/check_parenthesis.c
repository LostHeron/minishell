/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:18:43 by jweber            #+#    #+#             */
/*   Updated: 2025/06/25 16:26:03 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int	check_parenthesis(char *line)
{
	size_t	i;
	ssize_t	nb_parenthesis;

	nb_parenthesis = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '(')
			nb_parenthesis++;
		if (line[i] == ')')
			nb_parenthesis--;
		if (nb_parenthesis < 0)
		{
			return (ERROR_UNCLOSED_PARENTHESIS);
		}
		i++;
	}
	if (nb_parenthesis == 0)
		return (0);
	else
		return (ERROR_UNCLOSED_PARENTHESIS);
}
