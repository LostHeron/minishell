/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_pwd_env_not_null.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:54:52 by jweber            #+#    #+#             */
/*   Updated: 2025/07/22 12:55:25 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_init.h"
#include <unistd.h>
#include <stdio.h>

/* to check : 
 *	- case_value_not_null fail : DONE -> OK !
 *	- getcwd fail : DONE -> OK !
*/
int	case_pwd_env_not_null(t_minishell *p_mini, t_env *pwd_env)
{
	char	*ret_getcwd;

	if (pwd_env->value != NULL)
	{
		return (case_value_not_null(p_mini, pwd_env->value));
	}
	else
	{
		ret_getcwd = getcwd(p_mini->cwd_name, CWD_NAME_MAX_LENGTH);
		if (ret_getcwd == NULL)
		{
			perror("fn : initi_cwd_name : getcwd");
			return (-1);
		}
	}
	return (0);
}
