/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:07:15 by cviel             #+#    #+#             */
/*   Updated: 2025/08/04 19:43:50 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "expand.h"

void	free_exp(t_vector *word)
{
	size_t	i;

	i = 0;
	while (i < word->size)
	{
		free(((t_exp *)word->data)[i].content);
		i++;
	}
	free(word->data);
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
