/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:23:44 by jweber            #+#    #+#             */
/*   Updated: 2025/06/03 13:31:44 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lists_single.h"
#include "minishell.h"
#include "execution.h"
#include <unistd.h>
#include <stdio.h>

static void	print_path(t_minishell *p_mini);

int	init_minishell(t_minishell *p_mini, char **env)
{
	int	ret;

	p_mini->fd_stdin = dup(STDIN_FILENO);
	if (p_mini->fd_stdin == -1)
		perror(NULL);
	p_mini->fd_stdout = dup(STDOUT_FILENO);
	if (p_mini->fd_stdout == -1)
		perror(NULL);
	p_mini->fd_stderr = dup(STDERR_FILENO);
	if (p_mini->fd_stderr == -1)
		perror(NULL);
	ret = init_env(p_mini, env);
	if (ret != 0)
	{
		// do stuff;
		return (ret);
	}
	ret = init_path(p_mini);
	if (ret != 0)
	{
		// do stuff
		return (ret);
	}
	print_path(p_mini);
	return (0);
}

static void	print_path(t_minishell *p_mini)
{
	size_t	i;

	i = 0;
	while (i < p_mini->path.size)
	{
		printf("path[%zu] = %s\n", i, ((char **)p_mini->path.data)[i]);
		i++;
	}
}

/*
static void	print_env(t_minishell *p_mini, char **env)
{
	t_list	*tmp;
	int	i = 0;

	tmp = p_mini->env;
	while (tmp != NULL)
	{
		printf("key = %s\n", ((t_env *)tmp->content)->key);
		printf("value = %s\n", ((t_env *)tmp->content)->value);
		printf("\n");
		tmp = tmp->next;
		i++;
	}
}
*/
