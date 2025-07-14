/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_transform.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:34:32 by jweber            #+#    #+#             */
/*   Updated: 2025/07/14 13:43:23 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_string.h"
#include "ft_char.h"
#include "parsing.h"

static void	my_free(t_vector *ptr_vec);

int	here_doc_transform(t_list *env, char **p_line)
{
	t_vector	vec;
	int			ret;
	size_t		i;
	char		*key;
	char		*value;

	ret = ft_vector_init(&vec, ft_strlen((*p_line)) + 5, \
							sizeof(char), &my_free);
	if (ret != 0)
		return (ret);
	i = 0;
	while ((*p_line)[i])
	{
		while ((*p_line)[i] && (*p_line)[i] != '$')
			i++;
		if ((*p_line)[i] == '$')
		{
			if (ft_isalpha((*p_line)[i + 1]) == 0)
				i++;
			else
			{
				ret = ft_vector_add_multi(&vec, (*p_line), i);
				if (ret != 0)
				{
					ft_vector_free(&vec);
					return (ret);
				}
				key = get_key((*p_line) + i + 1);
				if (key == NULL)
				{
					ft_vector_free(&vec);
					return (ERROR_MALLOC);
				}
				value = get_value(env, key);
				if (value != NULL)
				{
					ret = ft_vector_add_multi(&vec, value, ft_strlen(value));
					if (ret != 0)
					{
						free(key);
						return (ret);
					}
				}
				i += ft_strlen(key) + 1;
				free(key);
				(*p_line) += i;
				i = 0;
			}
		}
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

static void	my_free(t_vector *ptr_vec)
{
	free(ptr_vec->data);
	return ;
}
