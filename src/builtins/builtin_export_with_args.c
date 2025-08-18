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
#include <asm-generic/errno-base.h>
#include <stdlib.h>

static int		check_key(char *str);
static int		valid_key(char *new_key, char *new_value, t_minishell *p_mini);
static t_env	*key_already_exists(char *new_key, t_minishell *p_mini);
static int		export_each_entry(t_minishell *p_mini, char *arg_i);

/* to check
 *	-> export_each_entry fail : DONE -> OK !
 */
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

/*	->This function should extract key and value from the user Nth input :
 * $ export user="yo man" age=25
 * 'user="yo man"' -> first input
 * 'age=25' -> secon input
 *	-> It then searches for the equal sign, left part of equal sign 
 *	is the key (or all if no equal sign), and right part is the value 
 *	(or NULL if no equal sign) 
 *	It then checks if the key is a valid identifier
 *		-> If it is it updates the environment value corresponding to that key
 *			-> If environment variable do not exists :
 *				create a new node containing the key and its associated value
 *			-> If it already exists:
 *				If value is not NULL it changes the value associated to the key
 *				else it does nothing
 *		-> If it is not a valid identifer it print a message saying so
 *		and return (1);
 * In case of failure function return a Negative integer
 * In case of sucess : 
 *	-> return (0) if key is valid identifier
 *	-> return (1) if key is not valid identifier
 * to check :
 *	-> get_new_key_value fail : DONE -> OK !
 *	-> ft_printf_fd fail : DONE -> OK !
 *	-> valid_key fail : DONE -> OK !
*/
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
		free(new_key);
		free(new_value);
		ret = ft_printf_fd(2, "export: `%s': not a valid identifier\n",
				arg_i);
		if (ret < 0)
			return (ERROR_WRITE);
		return (1);
	}
	else
	{
		return (valid_key(new_key, new_value, p_mini));
	}
}

/* This function check wether the key is a valid key
 * meaning the key begin either with an alpha of '_'
 * and contains only alnum or '_' char
 * return (1) if it is not a valid identifer
 * return (0) otherwise
*/
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
 * to check :
 *	-> key_already_exists can not fail : only return non NULL address
 *	if it finds an already existing structure whose key argument 
 *	is the same as new_key, else return NULL
 *	-> add_new_env fail : DONE -> OK !
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

/* function return a pointer to the t_env structure whose key is equal
 * to the new_key if it finds one,
 * or return NULL if no struct has a key which is equal to new_key
*/
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
