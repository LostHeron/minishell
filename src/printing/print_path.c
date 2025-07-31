/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:27:24 by jweber            #+#    #+#             */
/*   Updated: 2025/07/31 11:20:22 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include "minishell.h"
#include "execution.h"
#include "ft_io.h"

void	print_path(t_minishell *p_mini)
{
	size_t		i;
	int			ret;
	t_vector	path;

	i = 0;
	ft_printf_fd(2, "in print_path!\n");
	ret = get_path(p_mini, &path);
	if (ret != 0)
	{
		ft_vector_free(&path);
		return ;
	}
	while (i < path.size)
	{
		ft_printf_fd(2, "path[%u] = %s\n", i, ((char **)path.data)[i]);
		i++;
	}
	ft_vector_free(&path);
}
