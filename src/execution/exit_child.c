/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:18:07 by jweber            #+#    #+#             */
/*   Updated: 2025/07/15 15:18:33 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include "freeing.h"
#include "execution.h"

int	exit_child(t_minishell *p_mini, int ret)
{
	rl_clear_history();
	close_here_doc_fds(p_mini);
	close_saved_tty(p_mini);
	free_tree(&p_mini->head_ast);
	free_env(p_mini->env);
	free(p_mini->cwd_name);
	return (ret);
}
