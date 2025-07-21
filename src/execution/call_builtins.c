/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:43:15 by jweber            #+#    #+#             */
/*   Updated: 2025/07/21 14:42:54 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_string.h"
#include "ft_io.h"

int	call_builtins(t_minishell *p_mini, t_vector cmd_args)
{
	char	*cmd_name;
	size_t	i;

	cmd_name = ((char **)cmd_args.data)[0];
	i = 0;
	while (p_mini->builtins_name[i] != NULL)
	{
		if (ft_strcmp(p_mini->builtins_name[i], cmd_name) == 0)
		{
			return (p_mini->builtins_func[i](cmd_args, p_mini));
		}
		i++;
	}
	ft_printf_fd(2,
		"could not find which builtin to call, should not happend\n");
	ft_printf_fd(2,
		"tried to call builtin name : %s\n", cmd_name);
	exit(1);
}
