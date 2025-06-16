/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:29:40 by jweber            #+#    #+#             */
/*   Updated: 2025/06/16 17:48:43 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include "minishell.h"
#include "ft_io.h"
#include "ft_string.h"
#include <stdio.h>
#include <unistd.h>

int	builtin_cd(t_vector args, t_minishell *p_mini)
{
	int			ret;
	char		*place_to_go;

	if (args.size > 3)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	place_to_go = ((char **)args.data)[1];
	ret = chdir(place_to_go);
	if (ret == -1)
	{
		perror("cd: ");
		return (1);
	}
	else
	{
		if (place_to_go[0] == '/')
		{
			ft_strcpy(p_mini->path_name, place_to_go);
			p_mini->path_name_size = ft_strlen(place_to_go);
		}
		else
		{
			if (place_to_go[0] == '.' && place_to_go[1] == '/')
			{
				if (p_mini->path_name[p_mini->path_name_size - 1] != '/')
				{
					ft_strlcat(p_mini->path_name, \
						"/", PATH_NAME_MAX_LENGTH);
					p_mini->path_name_size += 1;
				}
				ft_strlcat(p_mini->path_name, \
					place_to_go + 2, PATH_NAME_MAX_LENGTH);
				p_mini->path_name_size += ft_strlen(place_to_go + 2);
			}
			else
			{
				if (p_mini->path_name[p_mini->path_name_size - 1] != '/')
				{
					ft_strlcat(p_mini->path_name, \
						"/", PATH_NAME_MAX_LENGTH);
					p_mini->path_name_size += 1;
				}
				ft_strlcat(p_mini->path_name, \
					place_to_go, PATH_NAME_MAX_LENGTH);
				p_mini->path_name_size += ft_strlen(place_to_go);
			}
		}
	}
	/*
	printf("current_working directory = %s\n", p_mini->path_name);
	printf("p_mini->path_name_size    = %zu\n", p_mini->path_name_size);
	*/
	return (0);
}
