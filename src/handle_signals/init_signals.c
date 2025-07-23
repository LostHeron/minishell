/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:11:36 by jweber            #+#    #+#             */
/*   Updated: 2025/06/24 19:15:28 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "handle_signal.h"
#include "ft_memory.h"

static void	handle_sigint(int sig);
static int	event_hook(void);

void	init_signals(void)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;

	g_my_signal = 0;
	ft_bzero(&sig_int, sizeof(struct sigaction));
	ft_bzero(&sig_quit, sizeof(struct sigaction));
	sig_int.sa_handler = &handle_sigint;
	sigaction(SIGINT, &sig_int, NULL);
	sig_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sig_quit, NULL);
	rl_event_hook = event_hook;
}

static void	handle_sigint(int sig)
{
	g_my_signal = sig;
	rl_done = 1;
	return ;
}

static int	event_hook(void)
{
	return (0);
}
