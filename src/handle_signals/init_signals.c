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
#include "handle_signal.h"
#include <stdlib.h>
#include <readline/readline.h>
#include "ft_memory.h"

static void	handle_sigint(int sig);
static int	event_hook(void);

void	init_signals(void)
{
	struct sigaction sig;

	my_signal = 0;
	ft_bzero(&sig, sizeof(struct sigaction));
	sig.sa_handler = &handle_sigint;
	sigaction(SIGINT, &sig, NULL);
	rl_event_hook = event_hook;
}

static void	handle_sigint(int sig)
{
	my_signal = sig;
	rl_done = 1;
	return ;
}

static int	event_hook(void)
{
	return (0);
}
