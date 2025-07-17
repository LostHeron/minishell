/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-23 13:02:57 by cviel             #+#    #+#             */
/*   Updated: 2025/06/23 18:35:35 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand.h"
#include "ft_vectors.h"
#include "ft_char.h"
#include "ft_string.h"

static int	expand_here(t_vector splitted, size_t vec_ind,
				int *p_ind, t_minishell mini);

int	expand_variables(t_vector splitted, t_minishell mini)
{
	int		ret;
	size_t	i;
	int		j;

	i = 0;
	while (i < splitted.size)
	{
		if (((t_exp *)splitted.data)[i].quote != SINGLE)
		{
			j = 0;
			while (((t_exp *)splitted.data)[i].content[j])
			{
				if (((t_exp *)splitted.data)[i].content[j] == '$')
				{
					ret = expand_here(splitted, i, &j, mini);
					if (ret != 0)
						return (ret);
				}
				else
					j++;
			}
		}
		i++;
	}
	return (0);
}

static t_env	*get_env(char *str, int ind, int len_key, t_minishell mini)
{
	t_list	*lst_i;

	lst_i = mini.env;
	while (lst_i != NULL
		&& (ft_strncmp(str + ind, ((t_env *)lst_i->content)->key, len_key) != 0
			|| ((t_env *)lst_i->content)->key[len_key] != 0))
		lst_i = lst_i->next;
	if (lst_i == NULL)
		return (NULL);
	return (lst_i->content);
}

static int	expand_here(t_vector splitted, size_t vec_ind,
				int *p_ind, t_minishell mini)
{
	t_exp	*p_exp_part;
	t_env	*p_env;
	int		len_key;

	p_exp_part = &((t_exp *)splitted.data)[vec_ind];
	if (p_exp_part->content[*p_ind + 1] == '\0' && vec_ind + 1 < splitted.size
		&& ((t_exp *)splitted.data)[vec_ind + 1].quote != NONE)
		return (remove_last(p_exp_part, *p_ind));
	if (p_exp_part->content[*p_ind + 1] == '?')
		return (replace_err_code(p_exp_part, p_ind, mini));
	if (ft_isalpha(p_exp_part->content[*p_ind + 1]) == 0
		&& p_exp_part->content[*p_ind + 1] != '_' )
	{
		(*p_ind)++;
		return (0);
	}
	len_key = 1;
	while (ft_isalnum(p_exp_part->content[*p_ind + len_key + 1]) != 0
		|| p_exp_part->content[*p_ind + len_key + 1] == '_' )
		len_key++;
	p_env = get_env(p_exp_part->content, *p_ind + 1, len_key, mini);
	return (replace_key_value(p_exp_part, p_ind, len_key, p_env));
}
