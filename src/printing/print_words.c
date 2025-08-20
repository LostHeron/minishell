/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:17:50 by jweber            #+#    #+#             */
/*   Updated: 2025/08/20 14:21:04 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include "expand.h"
#include <stdio.h>

void	print_word(t_vector vec)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < vec.size)
	{
		j = 0;
		while (j < ((t_vector *)vec.data)[i].size)
		{
			printf("%s, ",
				((t_exp *)((t_vector *)vec.data)[i].data)[j].content);
			j++;
		}
		printf("\n");
		i++;
	}
}
