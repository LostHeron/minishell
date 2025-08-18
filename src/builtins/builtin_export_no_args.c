/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_no_args.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:11:31 by jweber            #+#    #+#             */
/*   Updated: 2025/07/16 17:12:29 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_io.h"
#include <stdio.h>

static int	perror_return(void);

/* to check
 *	-> first ft_print_fd fail : DONE -> OK !
 *	-> second ft_printf_fd fail : DONE -> OK !
*/
int	builtin_export_no_args(t_minishell *p_mini)
{
	t_list	*tmp;

	tmp = p_mini->env;
	while (tmp != NULL)
	{
		if (((t_env *)tmp->content)->value != NULL)
		{
			if (ft_printf_fd(1, "export %s=\"%s\"\n",
					((t_env *)tmp->content)->key,
					((t_env *)tmp->content)->value) < 0)
				return (perror_return());
		}
		else
		{
			if (ft_printf_fd(1,
					"export %s\n", ((t_env *)tmp->content)->key) < 0)
				return (perror_return());
		}
		tmp = tmp->next;
	}
	return (0);
}

static int	perror_return(void)
{
	perror("write");
	return (ERROR_WRITE);
}
