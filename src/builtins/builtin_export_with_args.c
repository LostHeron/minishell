/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_with_args.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:10:37 by jweber            #+#    #+#             */
/*   Updated: 2025/06/17 18:26:19 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include "minishell.h"
#include "ft_char.h"
#include "ft_string.h"
#include "ft_standard.h"
#include "ft_io.h"
#include <stdlib.h>

static int		get_new_key_value(char *str, char **p_new_key, \
										char **p_new_value);
static int		check_key(char *str);
static int		valid_key(char *new_key, char *new_value, t_minishell *p_mini);
static t_env	*key_already_exists(char *new_key, t_minishell *p_mini);
static int		add_args_list(char *new_key, char *new_value, \
									t_minishell *p_mini);
static void		add_node_lst(t_minishell *p_mini, t_list *new_node);

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
			return (ERROR_MALLOC);
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

static int	get_new_key_value(char *str, char **p_new_key, char **p_new_value)
{
	char	*equal_position;

	equal_position = ft_strchr(str, '=');
	if (equal_position == NULL)
	{
		*p_new_key = ft_strdup(str);
		if (*p_new_key == NULL)
			return (ERROR_MALLOC);
		*p_new_value = NULL;
	}
	else
	{
		*p_new_key = ft_strndup(str, equal_position - str);
		if (*p_new_key == NULL)
			return (ERROR_MALLOC);
		*p_new_value = ft_strdup(equal_position + 1);
		if (*p_new_value == NULL)
		{
			free(*p_new_value);
			return (ERROR_MALLOC);
		}
	}
	return (0);
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
		ret = add_args_list(new_key, new_value, p_mini);
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

static int	add_args_list(char *new_key, char *new_value, t_minishell *p_mini)
{
	t_env	*new_env;
	t_list	*new_node;

	new_env = ft_malloc(sizeof(t_env));
	if (new_env == NULL)
		return (ERROR_MALLOC);
	new_env->key = new_key;
	new_env->value = new_value;
	new_node = ft_s_lstnew(new_env);
	if (new_node == NULL)
	{
		free(new_env->key);
		free(new_env->value);
		free(new_env);
		return (ERROR_MALLOC);
	}
	add_node_lst(p_mini, new_node);
	return (0);
}

static void	add_node_lst(t_minishell *p_mini, t_list *new_node)
{
	t_list	*tmp;

	if (p_mini->env == NULL)
	{
		p_mini->env = new_node;
		return ;
	}
	else
	{
		if (ft_strcmp(((t_env *)p_mini->env->content)->key, \
				((t_env *)new_node->content)->key) > 0)
		{
			new_node->next = p_mini->env;
			p_mini->env = new_node;
			return ;
		}
		else
		{
			tmp = p_mini->env;
			while (tmp->next != NULL)
			{
				if (ft_strcmp(((t_env *)tmp->next->content)->key, \
							((t_env *)new_node->content)->key) > 0)
				{
					new_node->next = tmp->next;
					tmp->next = new_node;
					return ;
				}
				tmp = tmp->next;
			}
			tmp->next = new_node;
			return ;
		}
	}
	return ;
}
