/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:29:40 by jweber            #+#    #+#             */
/*   Updated: 2025/06/12 18:35:50 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "ft_vectors.h"
#include "minishell.h"
#include "ft_io.h"
#include "ft_string.h"
#include <stdio.h>
#include <unistd.h>

int	cd(t_ast *ast, t_minishell *p_mini)
{
	t_vector	args;
	int			ret;
	char		*place_to_go;

	args = ast->arguments.com_args.content;
	if (args.size > 1)
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
			ft_strcpy(p_mini->path_name, place_to_go);
		else
		{
			if (place_to_go[0] == '.' && \
				place_to_go[0] != '\0' && \
				place_to_go[1] == '/')
				ft_strlcat(p_mini->path_name, \
					place_to_go + 2, PATH_NAME_MAX_LENGTH);
			else
				ft_strlcat(p_mini->path_name, \
					place_to_go, PATH_NAME_MAX_LENGTH);
		}
	}
	return (0);
}
