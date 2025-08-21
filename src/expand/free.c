/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:07:15 by cviel             #+#    #+#             */
/*   Updated: 2025/08/21 14:47:12 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "expand.h"
#include "ft_vectors.h"

void	free_exp(t_vector *p_word)
{
	size_t	i;

	i = 0;
	while (i < p_word->size)
	{
		free(((t_exp *)p_word->data)[i].content);
		i++;
	}
	free(p_word->data);
}

void	free_data(t_vector *p_vector)
{
	free(p_vector->data);
}

void	free_splitted(t_vector *p_word)
{
	size_t	i;

	i = 0;
	while (i < p_word->size)
	{
		ft_vector_free(&(((t_vector *)p_word->data)[i]));
		i++;
	}
	free(p_word->data);
}
