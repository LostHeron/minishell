/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:34:41 by jweber            #+#    #+#             */
/*   Updated: 2025/06/16 17:35:27 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_io.h"
#include <stdio.h>

int	builtin_pwd(t_vector args, t_minishell *p_mini)
{
	int	ret;

	if (args.size > 2)
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		return (1);
	}
	else
	{
		ret = printf("%s\n", p_mini->path_name);
		if (ret < 0)
		{
			perror("printf: ");
			return (ret);
		}
		else
		{
			return (0);
		}
	}
}
