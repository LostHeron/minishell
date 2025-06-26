/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:23:44 by jweber            #+#    #+#             */
/*   Updated: 2025/06/26 14:34:18 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "printing.h"
#include "ft_standard.h"
#include "ft_string.h"
#include <unistd.h>
#include <stdio.h>

static int		init_cwd_name(t_minishell *p_mini);
static t_env	*get_pwd_env(t_list *env);

/* 
 * This function should initiate the structe t_minishell,
 * it should fill all correct informaiton
 *	- in case of error, it must return a non null integer
 * and must free everything it has started allocated !
 *	- in case of success, it must return 0, and 
 *	have allocated everything correctly !
*/
int	init_minishell(t_minishell *p_mini, char **env)
{
	int	ret;

	p_mini->last_error_code = 0;
	ret = init_env(p_mini, env);
	if (ret != 0)
	{
		// do stuff ?
		return (ret);
	}
	ret = init_cwd_name(p_mini);
	if (ret != 0)
	{
		// do stuff;
		// free env
		return (ERROR_MALLOC);
	}
	/*
	ret = init_path(p_mini);
	if (ret != 0)
	{
		// do stuff
		// free path_name
		// free env
		return (ret);
	}
	*/
	init_builtins(p_mini);
	p_mini->fd_stdin = dup(STDIN_FILENO);
	if (p_mini->fd_stdin == -1)
		perror(NULL);
	p_mini->fd_stdout = dup(STDOUT_FILENO);
	if (p_mini->fd_stdout == -1)
		perror(NULL);
	p_mini->fd_stderr = dup(STDERR_FILENO);
	if (p_mini->fd_stderr == -1)
		perror(NULL);
	print_path(p_mini);
	return (0);
}

static int	init_cwd_name(t_minishell *p_mini)
{
	char	*ret;
	t_env	*pwd_env;

	p_mini->cwd_name = ft_malloc((CWD_NAME_MAX_LENGTH + 1) * sizeof(char));
	if (p_mini->cwd_name == NULL)
		return (ERROR_MALLOC);
	pwd_env = get_pwd_env(p_mini->env);
	if (pwd_env != NULL)
	{
		if (access(pwd_env->value, F_OK) == 0)
			ft_strcpy(p_mini->cwd_name, pwd_env->value);
		else
		{
			ret = getcwd(p_mini->cwd_name, CWD_NAME_MAX_LENGTH);
			if (ret == NULL)
			{
				// do stuff ?
				p_mini->cwd_name[0] = '\0';
				// or copy before function call and copy back after function call error ?
				return (1);
			}
			// and set path to current working dir ?
		}
	}
	else
	{
		ret = getcwd(p_mini->cwd_name, CWD_NAME_MAX_LENGTH);
		if (ret == NULL)
		{
			// do stuff ?
			p_mini->cwd_name[0] = '\0';
			// or copy before function call and copy back after function call error ?
			return (1);
		}
		// and set path to current working dir  ?
	}
	// and should add a verification of type $PWD inode == getcwd inode to see if we take from path or else where !
	return (0);
}

static t_env	*get_pwd_env(t_list *env)
{
	while (env != NULL)
	{
		if (ft_strcmp("PWD", ((t_env *)env->content)->key) == 0)
		{
			return (env->content);
		}
		env = env->next;
	}
	return (NULL);
}
