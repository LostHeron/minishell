/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:16:57 by jweber            #+#    #+#             */
/*   Updated: 2025/07/14 16:58:44 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_standard.h"
#include "ft_string.h"
#include "ft_vectors.h"
#include "handle_signal.h"
#include "minishell.h"
#include "parsing.h"
#include "ft_io.h"
#include <signal.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

static int	get_here_doc_i(t_minishell *p_mini, t_vector *p_tokens, int i,	\
															int *p_hd_count);
static int	close_all_here_doc(t_minishell *p_mini);
static void	ignore_sigquit(struct sigaction *p_old_s);
static void	restore_sigquit(struct sigaction *p_old_s);
static int	change_term_attr(struct termios *p_old_t);
static int	restore_term_attr(struct termios *p_old_t);

/* main function of here_doc
 * if an error occurs when calling get_here_doc_i,
 * the function should then free / close everything related to 
 * heredoc and return an error corresponding to the problem
 * to check : 
 *	-> get_here_doc_i fail : DONE -> OK !
 *	-> close_all_here_doc fail : NOT need to check, if we enter here
 *	we will already exit minishell, just trying to exit it well !
*/
int	get_here_doc(t_minishell *p_mini, t_vector *p_tokens)
{
	size_t				i;
	int					ret;
	int					hd_count;
	struct sigaction	old_s;
	struct termios		old_t;

	i = 0;
	hd_count = 0;
	if (isatty(0) == 1) 
	{
		ignore_sigquit(&old_s);
		change_term_attr(&old_t);
	}
	while (i < p_tokens->size)
	{
		ret = get_here_doc_i(p_mini, p_tokens, i, &hd_count);
		if (g_my_signal == SIGINT)
			ft_printf_fd(2, "^C");
		if (ret != 0)
		{
			if (isatty(0) == 1)
			{
				restore_term_attr(&old_t);
				restore_sigquit(&old_s);
			}
			close_all_here_doc(p_mini);
			return (ret);
		}
		i++;
	}
	if (isatty(0) == 1)
	{
		restore_term_attr(&old_t);
		restore_sigquit(&old_s);
	}
	return (0);
}

static void	ignore_sigquit(struct sigaction *p_old_s)
{
	struct sigaction	s;

	ft_bzero(&s, sizeof(struct sigaction));
	s.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &s, p_old_s);
	return ;
}

static void	restore_sigquit(struct sigaction *p_old_s)
{
	sigaction(SIGQUIT, p_old_s, NULL);
	return ;
}

static int	change_term_attr(struct termios *p_old_t)
{
	int				ret;
	struct termios	changed_t;

	ret = tcgetattr(0, p_old_t);
	if (ret < 0)
	{
		perror("tcgetattr");
		return (1);
	}
	changed_t = *p_old_t;
	changed_t.c_lflag &= ~ECHOCTL;
	ret = tcsetattr(0, 0, &changed_t);
	if (ret < 0)
	{
		perror("tcsetattr");
		return (1);
	}
	return (0);
}

static int	restore_term_attr(struct termios *p_old_t)
{
	int	ret;

	ret = tcsetattr(0, 0, p_old_t);
	if (ret < 0)
	{
		perror("tcsetattr");
		return (1);
	}
	return (0);
}

/* This function will handle one here_document
 * to check
 *	-> write_to_here_doc fail : DONE -> OK !
 *	-> ft_malloc fail : DONE -> OK !
*/
static int	get_here_doc_i(t_minishell *p_mini, t_vector *p_tokens, int i,	\
													int *p_hd_count)
{
	int	ret;

	if (ft_strcmp(((char **)p_tokens->data)[i], "<<") == 0)
	{
		ret = write_to_here_doc(p_mini, p_tokens, i, p_hd_count);
		if (ret != 0)
			return (ret);
		free(((char **)p_tokens->data)[i + 1]);
		((char **)p_tokens->data)[i + 1] = ft_malloc(2 * sizeof(char));
		if (((char **)p_tokens->data)[i + 1] == NULL)
			return (ERROR_MALLOC);
		((char **)p_tokens->data)[i + 1][0] = *p_hd_count;
		((char **)p_tokens->data)[i + 1][1] = '\0';
		(*p_hd_count)++;
	}
	return (0);
}

static int	close_all_here_doc(t_minishell *p_mini)
{
	size_t	i;
	int		final_ret;

	i = 0;
	final_ret = 0;
	while (i < NB_MAX_HERE_DOC)
	{
		if (p_mini->fds_here_doc[i] != -1)
		{
			if (close(p_mini->fds_here_doc[i]) < 0)
			{
				perror("fn: close_all_here_doc: close");
				final_ret = ERROR_CLOSE;
			}
		}
		i++;
	}
	return (final_ret);
}
