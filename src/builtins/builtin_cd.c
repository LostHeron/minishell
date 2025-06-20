/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:29:40 by jweber            #+#    #+#             */
/*   Updated: 2025/06/20 12:21:35 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lists_single.h"
#include "ft_vectors.h"
#include "minishell.h"
#include "ft_io.h"
#include "ft_string.h"
#include "builtins.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

static int	with_path_given(t_vector args, t_minishell *p_mini);
static char	*new_place_to_go(char *place_to_go, char *old_path);

int	builtin_cd(t_vector args, t_minishell *p_mini)
{
	int			ret;

	if (args.size > 3)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	else if (args.size == 2)
	{
		builtin_cd_without_path_given(p_mini);
		return (0);
	}
	else if (args.size == 3)
	{
		ret = with_path_given(args, p_mini);
		if (ret != 0)
		{
			return (ret);
		}
		return (ret);
	}
	else
	{
		ft_putstr_fd("args.size in builtin cd is wrong !\n", 2);
		exit(1);
	}
}

static int	with_path_given(t_vector args, t_minishell *p_mini)
{
	char		*place_to_go;
	int			ret;
	size_t		path_len;
	char		*path_name;

	place_to_go = ft_strdup(((char **)args.data)[1]);
	if (place_to_go == NULL)
		return (ERROR_MALLOC);
	if (place_to_go[0] != '/')
	{
		place_to_go = new_place_to_go(place_to_go, p_mini->path_name);
		if (place_to_go == NULL)
		{
			free(place_to_go);
			return (ERROR_MALLOC);
		}
	}
	ret = get_path_len_name(place_to_go, &path_len, &path_name);
	if (ret != 0)
	{
		free(place_to_go);
		return (ret);
	}
	ret = chdir(path_name);
	if (ret == -1)
	{
		free(place_to_go);
		free(path_name);
		perror("cd: ");
		return (1);
	}
	ft_strlcpy(p_mini->path_name, path_name, PATH_NAME_MAX_LENGTH);
	free(path_name);
	free(place_to_go);
	return (0);
}

static char	*new_place_to_go(char *place_to_go, char *old_path)
{
	char	*new_place_1;
	char	*new_place_2;

	new_place_1 = ft_strjoin(old_path, "/");
	if (new_place_1 == NULL)
		return (NULL);
	new_place_2 = ft_strjoin(new_place_1, place_to_go);
	if (new_place_2 == NULL)
	{
		free(new_place_1);
		return (NULL);
	}
	free(place_to_go);
	free(new_place_1);
	return (new_place_2);
}
