/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:23:44 by jweber            #+#    #+#             */
/*   Updated: 2025/07/01 18:46:37 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "printing.h"
#include "freeing.h"
#include "ft_init.h"
#include <unistd.h>
#include <stdio.h>

/* 
 * This function should initiate the structe t_minishell,
 * it should fill all correct informaiton
 *	- in case of error, it must return a non null integer
 * and must free everything it has started allocated !
 *	- in case of success, it must return 0, and 
 *	have allocated everything correctly !
 *	TO CHECK :
 *		- failure of init_env ; TO DO
 *		- failure of init_cwd_name ; TO DO
 *		- 
*/
int	init_minishell(t_minishell *p_mini, char **env)
{
	int	ret;

	p_mini->last_error_code = 0;
	ret = init_env(p_mini, env);
	if (ret != 0)
		return (ret);
	ret = init_cwd_name(p_mini);
	if (ret != 0)
	{
		free_env(p_mini->env);
		return (ERROR_MALLOC);
	}
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
