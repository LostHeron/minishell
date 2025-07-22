/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_from_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:27:04 by jweber            #+#    #+#             */
/*   Updated: 2025/07/18 12:41:26 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_vectors.h"
#include "ft_string.h"

static int	add_next_env(t_vector *p_new_env, t_list *env);
static int	case_value_not_null_env(t_list *env, char **p_str);
static void	my_free(t_vector *ptr_vec);

int	get_env_from_list(t_vector *p_new_env, t_list *env)
{
	int			ret;
	char		*null_string;

	ret = ft_vector_init(p_new_env, 5, sizeof(char *), &my_free);
	if (ret != 0)
		return (ret);
	while (env != NULL)
	{
		ret = add_next_env(p_new_env, env);
		if (ret != 0)
		{
			ft_vector_free(p_new_env);
			return (ret);
		}
		env = env->next;
	}
	null_string = NULL;
	ret = ft_vector_add_single(p_new_env, &null_string);
	if (ret != 0)
	{
		ft_vector_free(p_new_env);
		return (ret);
	}
	return (0);
}

static int	add_next_env(t_vector *p_new_env, t_list *env)
{
	int		ret;
	char	*str;

	if (((t_env *)env->content)->value != NULL)
	{
		ret = case_value_not_null_env(env, &str);
		if (ret != 0)
			return (ret);
		ret = ft_vector_add_single(p_new_env, &str);
		if (ret != 0)
			return (ret);
	}
	return (0);
}

static int	case_value_not_null_env(t_list *env, char **p_str)
{
	*p_str = ft_strjoin(((t_env *)env->content)->key, "=");
	if (*p_str == NULL)
		return (ERROR_MALLOC);
	*p_str = ft_strjoin_free_first(*p_str, ((t_env *)env->content)->value);
	if (*p_str == NULL)
		return (ERROR_MALLOC);
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
	return ;
}
