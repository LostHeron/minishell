/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:50:12 by jweber            #+#    #+#             */
/*   Updated: 2025/06/26 14:21:04 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_standard.h"
#include "ft_string.h"
#include "ft_vectors.h"
#include "minishell.h"

static int	add_path_to_path(t_vector *p_path, char *path_string);
static int	add_slash_to_path(t_vector *p_path);
static void	my_free(t_vector *ptr_vec);

int	get_path(t_minishell *p_mini, t_vector *p_path)
{
	int			ret;
	t_list		*tmp;

	ret = ft_vector_init(p_path, 5, sizeof(char *), &my_free);
	if (ret != 0)
	{
		// do stuff
		return (ret);
	}
	if (p_mini->env == NULL)
		return (0);
	tmp = p_mini->env;
	while (tmp != NULL && ft_strcmp("PATH", ((t_env *)tmp->content)->key) != 0)
		tmp = tmp->next;
	if (tmp == NULL)
	{
		return (0);
	}
	else
	{
		ret = add_path_to_path(p_path, ((t_env *)tmp->content)->value);
		if (ret != 0)
		{
			// do stuff 
			return (ret);
		}
		ret = add_slash_to_path(p_path);
		if (ret != 0)
		{
			// do stuff 
			return (ret);
		}
		return (0);
	}
}

static int	add_path_to_path(t_vector *p_path, char *path_string)
{
	size_t	i;
	int		ret;
	char	**split;

	if (path_string == NULL)
	{
		return (0);
	}
	split = ft_split(path_string, ":");
	if (split == NULL)
		return (ERROR_MALLOC);
	i = 0;
	while (split[i])
	{
		ret = ft_vector_add_single(p_path, split + i);
		if (ret != 0)
		{
			// do stuff
			return (ret);
		}
		i++;
	}
	free(split);
	return (0);
}

static int	add_slash_to_path(t_vector *p_path)
{
	size_t	len;
	size_t	i;
	//char	*new_path;

	i = 0;
	while (i < p_path->size)
	{
		len = ft_strlen(((char **)p_path->data)[i]);
		if (((char **)p_path->data)[i][len - 1] != '/')
		{
			((char **)p_path->data)[i] = \
				ft_strjoin_free_first(((char **)p_path->data)[i], "/");
			if (((char **)p_path->data)[i] == NULL)
			{
				return (ERROR_MALLOC);
			}
			/*
			new_path = ft_malloc((len + 2) * sizeof(char));
			if (new_path == NULL)
			{
				// do stuff 
				return (ERROR_MALLOC);
			}
			ft_strcpy(new_path, ((char **)p_mini->path.data)[i]);
			new_path[len] = '/';
			new_path[len + 1] = '\0';
			free(((char **)p_mini->path.data)[i]);
			((char **)p_mini->path.data)[i] = new_path;
			*/
		}
		i++;
	}
	return (0);
}

static void	my_free(t_vector *ptr_vec)
{
	size_t	i;

	i = 0;
	while (i < ptr_vec->size)
	{
		free(((char **)ptr_vec->data)[i]);
		i++;
	}
	free(ptr_vec->data);
}
