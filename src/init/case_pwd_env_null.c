/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_pwd_env_null.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:55:41 by jweber            #+#    #+#             */
/*   Updated: 2025/07/22 13:03:07 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

/* to check
 *	-> getcwd fail : DONE -> OK !
*/
int	case_pwd_env_null(t_minishell *p_mini)
{
	char	*ret_getcwd;

	ret_getcwd = getcwd(p_mini->cwd_name, CWD_NAME_MAX_LENGTH);
	if (ret_getcwd == NULL)
	{
		perror("fn : case_pwd_env_null : getcwd");
		return (1);
	}
	return (0);
}
