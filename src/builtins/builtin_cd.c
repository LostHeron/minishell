/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:29:40 by jweber            #+#    #+#             */
/*   Updated: 2025/06/26 14:25:41 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include "minishell.h"
#include "ft_io.h"
#include "ft_string.h"
#include "builtins.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

static int	with_path_given(t_vector args, t_minishell *p_mini);
static int	get_path_name(t_minishell *p_mini, char **p_place_to_go,\
							char **p_path_name, size_t	*p_path_len);
static char	*new_place_to_go(char *place_to_go, char *old_path);
static int	call_to_chdir(char **p_place_to_go, char *path_name);

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
		ret = builtin_cd_without_path_given(p_mini);
		return (ret);
	}
	else if (args.size == 3)
	{
		ret = with_path_given(args, p_mini);
		return (ret);
	}
	else
	{
		ft_putstr_fd("ERROR : args.size in builtin cd is wrong !\n", 2);
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
	ret = get_path_name(p_mini, &place_to_go, &path_name, &path_len);
	if (ret != 0)
		return (ret);
	ret = call_to_chdir(&place_to_go, path_name);
	if (ret != 0)
		return (ret);
	ft_strlcpy(p_mini->cwd_name, path_name, CWD_NAME_MAX_LENGTH);
	path_len = ft_strlen(place_to_go);
	if (path_len != 1 && place_to_go[path_len - 1] == '/'
		&& ft_strcmp(p_mini->cwd_name, "/") != 0)
		ft_strlcat(p_mini->cwd_name, "/", CWD_NAME_MAX_LENGTH);
	free(place_to_go);
	free(path_name);
	path_name = ft_strjoin("PWD=", p_mini->cwd_name);
	ret = export_from_string(path_name, p_mini);
	free(path_name);
	return (ret);
}

static int	get_path_name(t_minishell *p_mini, char **p_place_to_go,\
							char **p_path_name, size_t	*p_path_len)
{
	int	ret;

	if ((*p_place_to_go)[0] != '/')
	{
		(*p_place_to_go) = new_place_to_go(*p_place_to_go, p_mini->cwd_name);
		if ((*p_place_to_go) == NULL)
			return (ERROR_MALLOC);
	}
	ret = get_path_len_name(*p_place_to_go, p_path_len, p_path_name);
	if (ret != 0)
	{
		free(*p_place_to_go);
		return (ret);
	}
	return (0);
}

static char	*new_place_to_go(char *place_to_go, char *old_path)
{
	char	*new_place_1;
	char	*new_place_2;

	new_place_1 = ft_strjoin(old_path, "/");
	if (new_place_1 == NULL)
	{
		free(place_to_go);
		return (NULL);
	}
	new_place_2 = ft_strjoin(new_place_1, place_to_go);
	if (new_place_2 == NULL)
	{
		free(place_to_go);
		free(new_place_1);
		return (NULL);
	}
	free(place_to_go);
	free(new_place_1);
	return (new_place_2);
}

static int	call_to_chdir(char **p_place_to_go, char *path_name)
{
	int	ret;

	ret = chdir(path_name);
	if (ret == -1)
	{
		free(path_name);
		*p_place_to_go = ft_strjoin_free_second("cd: ", *p_place_to_go);
		if (*p_place_to_go == NULL)
		{
			return (ERROR_MALLOC);
		}
		perror(*p_place_to_go);
		free(*p_place_to_go);
		return (1);
	}
	return (0);
}
