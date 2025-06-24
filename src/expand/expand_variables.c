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

static int	expand_here(t_exp *p_exp_part, int *p_ind, t_minishell mini);

int	expand_variables(t_vector splitted, t_minishell mini)
{
	int	ret;
	size_t	i;
	int	j;

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
					ret = expand_here(&((t_exp *)splitted.data)[i], &j, mini);
					if (ret != 0)
						return (ret);
				}
				j++;
			}
		}
		i++;
	}
	return (0);
}

static t_env	*get_env(char *str, int	ind, int len_key, t_minishell mini)
{
	t_list	*lst_i;

	lst_i = mini.env;
	while (lst_i != NULL \
		&& (ft_strncmp(str + ind, ((t_env *)lst_i->content)->key, len_key) != 0 \
		|| ((t_env *)lst_i->content)->key[len_key] != 0))
		lst_i = lst_i->next;
	if (lst_i == NULL)
		return (NULL);
	return (lst_i->content);
}

static int	replace_key_value(t_exp *p_exp_part, int *p_ind, int len_key, t_env *p_env)
{
	char	*replace;
	int		len_replace;
	int		len_val;

	if (p_env == NULL)
		len_val = 0;
	else
		len_val = ft_strlen(p_env->value);
	len_replace = ft_strlen(p_exp_part->content) - (len_key + 1) + len_val + 1;
	replace = malloc(sizeof(char) * len_replace);
	if (replace == NULL)
		return (ERROR_MALLOC);
	*replace = '\0';
	ft_strncat(replace, p_exp_part->content, *p_ind);
	ft_strlcat(replace, p_env->value, len_replace);
	ft_strlcat(replace, p_exp_part->content + *p_ind + len_key + 1, len_replace);
	free(p_exp_part->content);
	p_exp_part->content = replace;
	return (0);
}

static int	expand_here(t_exp *p_exp_part, int *p_ind, t_minishell mini)
{
	t_env	*p_env;
	int		len_key;

	if (ft_isalpha(p_exp_part->content[*p_ind + 1]) == 0 \
		&& p_exp_part->content[*p_ind + 1] != '_' )
		return (0);
	len_key = 1;
	while (ft_isalnum(p_exp_part->content[*p_ind + len_key + 1]) != 0 \
			|| p_exp_part->content[*p_ind + len_key + 1] == '_' )
		len_key++;
	p_env = get_env(p_exp_part->content, *p_ind + 1, len_key, mini);
	return (replace_key_value(p_exp_part, p_ind, len_key, p_env));
}
