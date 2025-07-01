/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:47:21 by jweber            #+#    #+#             */
/*   Updated: 2025/07/01 17:48:26 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include "freeing.h"

void	free_minishell(t_minishell *p_mini)
{
	close(p_mini->fd_stdin);
	close(p_mini->fd_stdout);
	close(p_mini->fd_stderr);
	free_env(p_mini->env);
	free(p_mini->cwd_name);
}
