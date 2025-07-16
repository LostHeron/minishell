/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_with_args.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:10:37 by jweber            #+#    #+#             */
/*   Updated: 2025/07/16 17:17:17 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include "minishell.h"
#include "ft_char.h"
#include "ft_string.h"
#include "ft_io.h"
#include "builtins.h"
#include <stdlib.h>

static int		check_key(char *str);
static int		valid_key(char *new_key, char *new_value, t_minishell *p_mini);
static t_env	*key_already_exists(char *new_key, t_minishell *p_mini);
static int		export_each_entry(t_minishell *p_mini, char *arg_i);

int	builtin_export_with_args(t_vector args, t_minishell *p_mini)
{
	size_t	i;
	int		ret;
	int		final_ret;

	i = 1;
	ret = 0;
	final_ret = 0;
	while (i < args.size - 1)
	{
		ret = export_each_entry(p_mini, ((char **)args.data)[i]);
		if (ret != 0)
		{
			if (ret < 0)
				return (ret);
			else
				final_ret = 1;
		}
		i++;
	}
	return (final_ret);
}

static int	export_each_entry(t_minishell *p_mini, char *arg_i)
{
	int		ret;
	char	*new_key;
	char	*new_value;

	ret = get_new_key_value(arg_i, &new_key, &new_value);
	if (ret != 0)
		return (ret);
	if (check_key(new_key) != 0)
	{
		ft_printf_fd(2, "export: `%s': not a valid identifier\n",
			arg_i);
		free(new_key);
		free(new_value);
		ret = 1;
	}
	else
	{
		ret = valid_key(new_key, new_value, p_mini);
		if (ret != 0)
			return (ret);
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

/*	function will deal correctly with new_key and new_value)
 *	in any case new_key and new_value will be freed in this function
 * if needed
 *	in case of success :
 *		return (0) and the new environnement is correctly make !
 *	in case of failure : 
 *		return a negative integer a malloc error, 
 *		program should must make the error go up and 
 *		exit the shell !
*/
static int	valid_key(char *new_key, char *new_value, t_minishell *p_mini)
{
	int		ret;
	t_env	*existing_env;

	existing_env = key_already_exists(new_key, p_mini);
	if (existing_env != NULL)
	{
		free(new_key);
		if (new_value != NULL)
		{
			free(existing_env->value);
			existing_env->value = new_value;
			return (0);
		}
	}
	else
	{
		ret = add_new_env(new_key, new_value, p_mini);
		if (ret != 0)
		{
			free(new_value);
			free(new_key);
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
