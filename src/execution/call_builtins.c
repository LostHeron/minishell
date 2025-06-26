/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:43:15 by jweber            #+#    #+#             */
/*   Updated: 2025/06/26 13:44:26 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_string.h"

int	call_builtins(t_minishell *p_mini, t_vector cmd_args)
{
	char	*cmd_name;
	size_t	i;
	int		ret;

	cmd_name = ((char **)cmd_args.data)[0];
	i = 0;
	while (p_mini->builtins_name[i] != NULL)
	{
		if (ft_strcmp(p_mini->builtins_name[i], cmd_name) == 0)
		{
			ret = p_mini->builtins_func[i](cmd_args, p_mini);
			if (ret != 0)
			{
				//do stuff ?
			}
			return (ret);
		}
		i++;
	}
	return (1);
}
