/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:02:21 by jweber            #+#    #+#             */
/*   Updated: 2025/06/30 13:15:36 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include "ft_string.h"

int	count_here_doc(t_vector tokens)
{
	int		nb_here_doc;
	size_t	i;

	nb_here_doc = 0;
	i = 0;
	while (i < tokens.size)
	{
		if (ft_strcmp(((char **)tokens.data)[i], "<<") == 0)
		{
			nb_here_doc++;
		}
		if (nb_here_doc > 16)
		{
			return (1);
		}
		i++;
	}
	return (0);
}
