/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:01:57 by jweber            #+#    #+#             */
/*   Updated: 2025/07/21 14:26:55 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_vectors.h"
#include <unistd.h>

int	find_command(char **p_cmd, t_vector path)
{
	size_t	i;
	char	*new_cmd;

	i = 0;
	while (i < path.size)
	{
		new_cmd = ft_strjoin(((char **)path.data)[i], *p_cmd);
		if (new_cmd == NULL)
			return (ERROR_MALLOC);
		if (access(new_cmd, F_OK) == 0)
		{
			free(*p_cmd);
			*p_cmd = new_cmd;
			return (0);
		}
		free(new_cmd);
		i++;
	}
	if (path.size == 0)
		if (access(*p_cmd, F_OK) == 0)
			return (0);
	return (1);
}
