/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:34:41 by jweber            #+#    #+#             */
/*   Updated: 2025/06/26 14:26:45 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_io.h"
#include <stdio.h>

int	builtin_pwd(t_vector args, t_minishell *p_mini)
{
	int	ret;

	(void) args;
	ret = ft_printf_fd(1, "%s\n", p_mini->cwd_name);
	if (ret < 0)
	{
		perror("printf: ");
		return (ERROR_WRITE);
	}
	else
	{
		return (0);
	}
}
