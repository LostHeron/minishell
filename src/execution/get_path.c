/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:50:12 by jweber            #+#    #+#             */
/*   Updated: 2025/07/17 17:52:19 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_standard.h"
#include "ft_string.h"
#include "ft_vectors.h"
#include "minishell.h"
#include <stdio.h>

static int	fill_vector_with_paths(t_vector *p_path, t_list *tmp);
static int	add_path_to_path(t_vector *p_path, char *path_string);
static void	clear_vector_data(t_vector *ptr_vec);
static void	my_free(t_vector *ptr_vec);
int			add_slash_to_path(t_vector *p_path);

/* This function initialize a t_vector 'path, passed via
 * its address, and fill it with the different path from PATH
 * environment variable
 * in case of success:
 *  -> return (0) and have correctly initialize path
 * in case of failure:
 *  -> return the corresponding error code and free
 *     everything that has been allocated
 * to check
 *	-> ft_vector_init_fail : DONE -> OK !
 *	-> fill_vector_with_paths fail : DONE -> OK !
*/
int	get_path(t_minishell *p_mini, t_vector *p_path)
{
	int			ret;
	t_list		*tmp;

	ret = ft_vector_init(p_path, 5, sizeof(char *), &my_free);
	if (ret != 0)
		return (ret);
	if (p_mini->env == NULL)
		return (0);
	tmp = p_mini->env;
	while (tmp != NULL && ft_strcmp("PATH", ((t_env *)tmp->content)->key) != 0)
		tmp = tmp->next;
	if (tmp == NULL)
		return (0);
	else
	{
		ret = fill_vector_with_paths(p_path, tmp);
		if (ret != 0)
		{
			ft_vector_free(p_path);
			return (ret);
		}
		return (0);
	}
}

/* to check
 *	-> add_path_to_path fail : DONE -> OK !
 *	-> add_slash_to_path fail : DONE -> OK !
*/
static int	fill_vector_with_paths(t_vector *p_path, t_list *tmp)
{
	int	ret;

	ret = add_path_to_path(p_path, ((t_env *)tmp->content)->value);
	if (ret != 0)
	{
		return (ret);
	}
	ret = add_slash_to_path(p_path);
	if (ret != 0)
	{
		return (ret);
	}
	return (0);
}

/* to check
 *	-> ft_split fail : DONE -> OK !
 *	-> ft_vector_add_single fail : DONE -> OK !
*/
static int	add_path_to_path(t_vector *p_path, char *path_string)
{
	size_t	i;
	int		ret;
	char	**split;

	if (path_string == NULL)
		return (0);
	split = ft_split(path_string, ":");
	if (split == NULL)
		return (ERROR_MALLOC);
	i = 0;
	while (split[i])
	{
		ret = ft_vector_add_single(p_path, split + i);
		if (ret != 0)
		{
			clear_vector_data(p_path);
			ft_split_free(split);
			return (ret);
		}
		i++;
	}
	free(split);
	return (0);
}

/* This function is called when ft_vector_add_single fail
 * while it was adding elements from splitted data to the vector
 * this is necessary because in case of failure, we need to free 
 * the splitted data, but also free the vector, we can not simply 
 * free the vector, because if vector had filled half of the data
 * from splitted data, we will either have DOUBLE FREE or NOT FREEED
 * all the data !
*/
static void	clear_vector_data(t_vector *ptr_vec)
{
	size_t	i;

	i = 0;
	while (i < ptr_vec->size)
	{
		((char **)ptr_vec->data)[i] = NULL;
		i++;
	}
	ptr_vec->size = 0;
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
	ptr_vec->size = 0;
	ptr_vec->capacity = 0;
}
