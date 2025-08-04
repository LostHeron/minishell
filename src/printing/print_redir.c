/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:02:17 by jweber            #+#    #+#             */
/*   Updated: 2025/08/04 14:08:05 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include "ast.h"
#include "ft_io.h"

void	print_redir(t_vector redir_vec)
{
	size_t	i;

	i = 0;
	while (i < redir_vec.size)
	{
		ft_printf_fd(1, "type = %i, filename = %s\n",
			((t_dirargs *)redir_vec.data)[i].dir,
			((t_dirargs *)redir_vec.data)[i].filename);
		i++;
	}
}
