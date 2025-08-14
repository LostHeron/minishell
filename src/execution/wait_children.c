/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:20:13 by jweber            #+#    #+#             */
/*   Updated: 2025/07/21 14:44:42 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "minishell.h"
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include "ft_io.h"

static void	get_child_return_value(t_minishell *p_mini,
				int child_ret, int *p_ret);
static void	set_ign_sigint(struct sigaction *s);
static void	un_set_ign_sigint(struct sigaction *s);

/* this function should wait for nb_wait children to finish their execution 
 * while retreiving exit code of the last process that as been started */
int	wait_children(t_minishell *p_mini, int nb_wait)
{
	int					child_ret;
	int					ret;
	int					wait_id;
	struct sigaction	old_s;
	int					i;

	ret = 0;
	set_ign_sigint(&old_s);
	i = 0;
	while (i < nb_wait)
	{
		wait_id = wait(&child_ret);
		p_mini->nb_child_to_wait--;
		i++;
		if (wait_id == p_mini->last_child_id)
		{
			get_child_return_value(p_mini, child_ret, &ret);
		}
	}
	un_set_ign_sigint(&old_s);
	return (ret);
}

static void	set_ign_sigint(struct sigaction *p_old_s)
{
	struct sigaction	new_s;

	ft_bzero(&new_s, sizeof(struct sigaction));
	new_s.sa_handler = SIG_IGN;
	sigaction(SIGINT, &new_s, p_old_s);
	return ;
}

static void	un_set_ign_sigint(struct sigaction *p_old_s)
{
	sigaction(SIGINT, p_old_s, NULL);
	return ;
}

static void	get_child_return_value(t_minishell *p_mini,
							int child_ret, int *p_ret)
{
	if (WIFEXITED(child_ret) != 0)
	{
		p_mini->last_error_code = WEXITSTATUS(child_ret);
		*p_ret = 0;
	}
	else if (WIFSIGNALED(child_ret) != 0)
	{
		p_mini->last_error_code = WTERMSIG(child_ret);
		if (p_mini->last_error_code == SIGQUIT)
			ft_printf_fd(1, "Quit (core dumped)");
		ft_printf_fd(1, "\n");
		p_mini->last_error_code += 128;
		*p_ret = 0;
	}
	else
		*p_ret = 1;
	return ;
}
