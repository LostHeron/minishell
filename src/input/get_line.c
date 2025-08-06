/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 10:30:35 by jweber            #+#    #+#             */
/*   Updated: 2025/08/06 10:45:01 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_input.h"
#include "handle_signal.h"
#include "ft_io.h"
#include "ft_string.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static void	case_zero_one_tty(t_minishell *p_mini, char **p_line, int *p_ret);
static void	case_only_zero_tty(t_minishell *p_mini, char **p_line, int *p_ret);

/* to check
 *	-> get_prompt_fail : DONE -> OK ;
 *	-> *p_line = NULL and *p_ret != 0 : DONE -> OK !
 *	-> readline = NULL : DONE -> OK !
*/
void	get_line(t_minishell *p_mini, char **p_line, int *p_ret)
{
	size_t	len;

	*p_ret = 0;
	if (isatty(0) == 1 && isatty(1) == 1)
	{
		case_zero_one_tty(p_mini, p_line, p_ret);
		if (*p_line == NULL || *p_ret != 0 || g_my_signal != 0)
		{
			return ;
		}
		/*
		prompt = get_prompt(p_mini);
		if (prompt == NULL)
		{
			*p_ret = ERROR_MALLOC;
			return ;
		}
		ret = rl_gnl(p_line, prompt);
		free(prompt);
		if (*p_line == NULL)
			return ;
		if (ret != 0)
		{
			*p_ret = ret;
			return ;
		}
		if (g_my_signal != 0)
		{
			return ;
		}
		*/
	}
	else if (isatty(0) == 1)
	{
		case_only_zero_tty(p_mini, p_line, p_ret);
		if (*p_line == NULL || *p_ret != 0 || g_my_signal != 0)
		{
			return ;
		}
		/*
		if (dup2(p_mini->fd_tty_in, 1) < 0)
		{
			perror("dup2");
		}
		prompt = get_prompt(p_mini);
		if (prompt == NULL)
		{
			*p_ret = ERROR_MALLOC;
			return ;
		}
		ret = rl_gnl(p_line, prompt);
		if (dup2(p_mini->fd_tty_out, 1) < 0)
		{
			perror("dup2");
		}
		free(prompt);
		if (*p_line == NULL)
			return ;
		if (ret != 0)
		{
			*p_ret = ret;
			return ;
		}
		if (g_my_signal != 0)
		{
			return ;
		}
		*/
	}
	else
	{
		*p_line = get_next_line(0, p_ret);
	}
	if (*p_line != NULL)
	{
		len = ft_strlen(*p_line);
		if ((*p_line)[len - 1] == '\n')
			(*p_line)[len - 1] = '\0';
	}
	return ;
}

static void	case_zero_one_tty(t_minishell *p_mini, char **p_line, int *p_ret)
{
	char	*prompt;

	prompt = get_prompt(p_mini);
	if (prompt == NULL)
	{
		*p_ret = ERROR_MALLOC;
		return ;
	}
	*p_ret = rl_gnl(p_line, prompt);
	free(prompt);
}

static void	case_only_zero_tty(t_minishell *p_mini, char **p_line, int *p_ret)
{
	if (dup2(p_mini->fd_tty_in, 1) < 0)
	{
		perror("dup2");
		*p_ret = ERROR_DUP2;
		return ;
	}
	case_zero_one_tty(p_mini, p_line, p_ret);
	if (dup2(p_mini->fd_tty_out, 1) < 0)
	{
		perror("dup2");
		*p_ret = ERROR_DUP2;
		return ;
	}
}
