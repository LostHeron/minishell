/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:27:24 by jweber            #+#    #+#             */
/*   Updated: 2025/06/03 16:33:27 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	print_path(t_minishell *p_mini)
{
	size_t	i;

	i = 0;
	printf("in print_path!\n");
	fflush(stdout);
	while (i < p_mini->path.size)
	{
		printf("path[%zu] = %s\n", i, ((char **)p_mini->path.data)[i]);
		i++;
	}
}
