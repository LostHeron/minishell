/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_with_args.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:10:37 by jweber            #+#    #+#             */
/*   Updated: 2025/06/20 15:41:53 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include "minishell.h"
#include "ft_char.h"
#include "ft_string.h"
#include "ft_standard.h"
#include "ft_io.h"
#include "builtins.h"
#include <stdlib.h>

static int		check_key(char *str);
static int		valid_key(char *new_key, char *new_value, t_minishell *p_mini);
static t_env	*key_already_exists(char *new_key, t_minishell *p_mini);

int	builtin_export_with_args(t_vector args, t_minishell *p_mini)
{
	size_t	i;
	int		ret;
	char	*new_key;
	char	*new_value;

	i = 1;
	ret = 0;
	while (i < args.size - 1)
	{
		ret = get_new_key_value(((char **)args.data)[i], &new_key, &new_value);
		if (ret != 0)
		{
			return (ret);
		}
		if (check_key(new_key) != 0)
		{
			ft_printf_fd(2, "export: `%s': not a valid identifier\n", \
							((char **)args.data)[i]);
			free(new_key);
			free(new_value);
			ret = 1;
		}
		else
		{
			ret = valid_key(new_key, new_value, p_mini);
			if (ret != 0)
			{
				// do stuff ?
				return (ret);
			}
		}
		i++;
	}
	return (ret);
}

static int	check_key(char *str)
{
	size_t	i;

	i = 0;
	if (ft_isalpha(str[i]) == 0 && str[i] != '_')
	{
		return (1);
	}
	i++;
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

static int	valid_key(char *new_key, char *new_value, t_minishell *p_mini)
{
	int		ret;
	t_env	*existing_env;

	existing_env = key_already_exists(new_key, p_mini);
	if (existing_env != NULL)
	{
		if (new_value != NULL)
		{
			free(existing_env->value);
			existing_env->value = new_value;
			free(new_key);
			return (0);
		}
		else
		{
			free(new_value);
			free(new_key);
		}
	}
	else
	{
		ret = add_new_env(new_key, new_value, p_mini);
		if (ret != 0)
		{
			// do stuff ?
			return (ret);
		}
	}
	return (0);
}

static t_env	*key_already_exists(char *new_key, t_minishell *p_mini)
{
	t_list	*tmp;

	tmp = p_mini->env;
	while (tmp != NULL)
	{
		if (ft_strcmp(new_key, ((t_env *)tmp->content)->key) == 0)
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}
