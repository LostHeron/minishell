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

static void	get_child_return_value(t_minishell *p_mini,\
									int child_ret, int *p_ret);
static void	set_ign_sigint(struct sigaction *s);
static void	un_set_ign_sigint(struct sigaction *s);

int	wait_children(t_minishell *p_mini)
{
	int					child_ret;
	int					ret;
	int					wait_id;
	struct sigaction	s[2];

	ret = 0;
	set_ign_sigint(s);
	while (p_mini->nb_child_to_wait > 0)
	{
		wait_id = wait(&child_ret);
		p_mini->nb_child_to_wait--;
		if (wait_id == p_mini->last_child_id)
		{
			get_child_return_value(p_mini, child_ret, &ret);
		}
	}
	un_set_ign_sigint(s);
	return (ret);
	/*
	if (p_mini->last_child_id != 0)
	{
		set_ign_sigint(s);
		while (p_mini->nb_child_to_wait > 0)
		{
			wait_id = wait(&child_ret);
			p_mini->nb_child_to_wait--;
			if (wait_id == p_mini->last_child_id)
			{
				get_child_return_value(p_mini, child_ret, &ret);
			}
		}
		un_set_ign_sigint(s);
		return (ret);
	}
	else
	{
		return (0);
	}
	*/
}

static void	set_ign_sigint(struct sigaction *s)
{
	ft_bzero(s + 0, sizeof(struct sigaction));
	s[0].sa_handler = SIG_IGN;
	sigaction(SIGINT, s + 0, s + 1);
	return ;
}

static void	un_set_ign_sigint(struct sigaction *s)
{
	sigaction(SIGINT, s + 1, NULL);
	return ;
}

static void	get_child_return_value(t_minishell *p_mini,\
									int child_ret, int *p_ret)
{
	if (WIFEXITED(child_ret) != 0)
	{
		p_mini->last_error_code = WEXITSTATUS(child_ret);
		*p_ret = 0;
	}
	else if (WIFSIGNALED(child_ret) != 0)
	{
		printf("\n");
		p_mini->last_error_code = WTERMSIG(child_ret);
		p_mini->last_error_code += 128;
		*p_ret = 0;
	}
	else
		*p_ret = 1;
	return ;
}
