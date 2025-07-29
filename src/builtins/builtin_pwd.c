/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:34:41 by jweber            #+#    #+#             */
/*   Updated: 2025/07/29 18:22:23 by cviel            ###   ########.fr       */
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
		ret = ft_printf_fd(1, "%s\n", p_mini->cwd_name);
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
