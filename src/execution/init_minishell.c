/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:23:44 by jweber            #+#    #+#             */
/*   Updated: 2025/06/03 16:32:07 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "printing.h"
#include "ft_standard.h"
#include <unistd.h>
#include <stdio.h>

static int	init_path_name(t_minishell *p_mini);

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

	ret = init_env(p_mini, env);
	if (ret != 0)
	{
		// do stuff ?
		return (ret);
	}
	ret = init_path_name(p_mini);
	if (ret != 0)
	{
		// do stuff;
		// free env
		return (ERROR_MALLOC);
	}
	ret = init_path(p_mini);
	if (ret != 0)
	{
		// do stuff
		// free path_name
		// free env
		return (ret);
	}
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

static int	init_path_name(t_minishell *p_mini)
{
	p_mini->path_name = ft_malloc(PATH_NAME_MAX_LENGTH * sizeof(char));
	if (p_mini->path_name == NULL)
		return (ERROR_MALLOC);
	p_mini->path_name_size = 0;
	p_mini->path_name[0] = '\0';
	
	return (0);
}
