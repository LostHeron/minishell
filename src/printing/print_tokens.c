/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:31:10 by jweber            #+#    #+#             */
/*   Updated: 2025/07/31 12:32:57 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include "ft_io.h"

void	print_tokens(t_vector tokens)
{
	size_t	i;

	i = 0;
	ft_printf_fd(2, "tokens : ");
	while (i < tokens.size)
	{
		ft_printf_fd(2, "'%s', ", ((char **)tokens.data)[i]);
		i++;
	}
	ft_printf_fd(2, "\n");
}
