/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:35:36 by jweber            #+#    #+#             */
/*   Updated: 2025/06/16 17:35:54 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	builtin_echo(t_vector args, t_minishell *p_mini)
{
	size_t	i;

	i = 1;
	(void) p_mini;
	while (i < args.size - 1)
	{
		printf("%s", ((char **)args.data)[i]);
		if (i != args.size - 2)
			printf(" ");
		i++;
	}
	printf("\n");
	return (0);
}
