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

static void	handle_sigint(int sig);

void	init_signals(void)
{
	struct sigaction sig;

	sig.sa_handler = &handle_sigint;
	sigaction(SIGINT, &sig, NULL);
}

static void	handle_sigint(int sig)
{
	(void) sig;
	return ;
}
