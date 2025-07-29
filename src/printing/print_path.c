/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:27:24 by jweber            #+#    #+#             */
/*   Updated: 2025/07/29 18:23:24 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include "minishell.h"
#include "execution.h"
#include "ft_io.h"
#include <stdio.h>

void	print_path(t_minishell *p_mini)
{
	size_t		i;
	int			ret;
	t_vector	path;

	i = 0;
	ft_printf_fd(1, "in print_path!\n");
	fflush(stdout);
	ret = get_path(p_mini, &path);
	if (ret != 0)
	{
		ft_vector_free(&path);
		return ;
	}
	while (i < path.size)
	{
		ft_printf_fd(1, "path[%zu] = %s\n", i, ((char **)path.data)[i]);
		i++;
	}
	ft_vector_free(&path);
}
