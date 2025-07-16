/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_transform.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:34:32 by jweber            #+#    #+#             */
/*   Updated: 2025/07/14 17:34:44 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include "minishell.h"
#include "ft_string.h"
#include "ft_char.h"
#include "parsing.h"

static int	create_new_line(t_list *env, t_vector *p_vec,\
								char **p_line, size_t *p_i);
static int	key_is_valid(t_list *env, t_vector *p_vec,\
								char **p_line, size_t *p_i);
static int	handle_value(t_list *env, t_vector *p_vec, char *key);
static void	my_free(t_vector *ptr_vec);

int	here_doc_transform(t_list *env, char **p_line)
{
	t_vector	vec;
	int			ret;
	size_t		i;

	ret = ft_vector_init(&vec, ft_strlen((*p_line)) + 5, \
sizeof(char), &my_free);
	if (ret != 0)
		return (ret);
	i = 0;
	while ((*p_line)[i])
	{
		ret = create_new_line(env, &vec, p_line, &i);
		if (ret != 0)
			return (ret);
	}
	ret = ft_vector_add_multi(&vec, (*p_line), i);
	if (ret != 0)
	{
		ft_vector_free(&vec);
		return (ret);
	}
	((char *)vec.data)[vec.size] = '\0';
	(*p_line) = vec.data;
	return (0);
}

static int	create_new_line(t_list *env, t_vector *p_vec,\
									char **p_line, size_t *p_i)
{
	int	ret;

	while ((*p_line)[*p_i] && (*p_line)[*p_i] != '$')
		(*p_i)++;
	if ((*p_line)[(*p_i)] == '$')
	{
		if (ft_isalpha((*p_line)[(*p_i) + 1]) == 0
								&& (*p_line)[(*p_i) + 1] != '_')
			(*p_i)++;
		else
		{
			ret = key_is_valid(env, p_vec, p_line, p_i);
			if (ret != 0)
			{
				// something else ?
				return (ret);
			}
		}
	}
	return (0);
}

static int	key_is_valid(t_list *env, t_vector *p_vec,\
								char **p_line, size_t *p_i)
{
	int		ret;
	char	*key;

	ret = ft_vector_add_multi(p_vec, (*p_line), *p_i);
	if (ret != 0)
	{
		ft_vector_free(p_vec);
		return (ret);
	}
	key = get_key((*p_line) + *p_i + 1);
	if (key == NULL)
	{
		ft_vector_free(p_vec);
		return (ERROR_MALLOC);
	}
	ret = handle_value(env, p_vec, key);
	if (ret != 0)
		return (ret);
	*p_i += ft_strlen(key) + 1;
	free(key);
	*p_line += (*p_i);
	*p_i = 0;
	return (0);
}

static int	handle_value(t_list *env, t_vector *p_vec, char *key)
{
	char	*value;
	int		ret;

	value = get_value(env, key);
	if (value != NULL)
	{
		ret = ft_vector_add_multi(p_vec, value, ft_strlen(value));
		if (ret != 0)
		{
			free(key);
			return (ret);
		}
	}
	return (0);
}

static void	my_free(t_vector *ptr_vec)
{
	free(ptr_vec->data);
	return ;
}
