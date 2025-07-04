/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_before_after.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:24:51 by jweber            #+#    #+#             */
/*   Updated: 2025/07/04 16:25:57 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include "parsing.h"

int	check_before_after(t_vector tokens, size_t i)
{
	if (check_before(tokens, i) != 0)
		return (1);
	if (check_after(tokens, i) != 0)
		return (1);
	return (0);
}
