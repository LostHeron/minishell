/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:23:44 by jweber            #+#    #+#             */
/*   Updated: 2025/08/06 10:21:38 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "freeing.h"
#include "ft_init.h"
#include <unistd.h>

static void	init_fds(t_minishell *p_mini);

/* 
 * This function should initiate the structe t_minishell,
 * it should fill all correct informaiton
 *	- in case of error, it must return a non null integer
 * and must free everything it has started allocated !
 *	- in case of success, it must return 0, and 
 *	have allocated everything correctly !
 *	TO CHECK :
 *		- failure of init_env ; DONE -> OK !
 *		- failure of init_cwd_name ; DONE -> OK !
 *		- failure of dup(STDIN_FILENO); DONE -> OK !
*/
int	init_minishell(t_minishell *p_mini, char **env)
{
	int	ret;

	p_mini->last_error_code = 0;
	p_mini->nb_child_to_wait = 0;
	p_mini->print_error = 1;
	init_fds(p_mini);
	ret = init_env(p_mini, env);
	if (ret != 0)
		return (ret);
	ret = init_cwd_name(p_mini);
	if (ret != 0)
	{
		free_env(p_mini->env);
		return (ret);
	}
	init_builtins(p_mini);
	ret = init_saved_tty(p_mini);
	return (ret);
}

static void	init_fds(t_minishell *p_mini)
{
	p_mini->fd1[0] = -1;
	p_mini->fd1[1] = -1;
	p_mini->fd2[0] = -1;
	p_mini->fd2[1] = -1;
}
