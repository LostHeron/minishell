/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:49:02 by jweber            #+#    #+#             */
/*   Updated: 2025/07/01 18:12:20 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

static void	init_builtins_func(t_minishell *p_mini);
static void	init_builtins_name(t_minishell *p_mini);

void	init_builtins(t_minishell *p_mini)
{
	init_builtins_name(p_mini);
	init_builtins_func(p_mini);
	return ;
}

static void	init_builtins_name(t_minishell *p_mini)
{
	p_mini->builtins_name[BUILTINS_CD] = "cd";
	p_mini->builtins_name[BUILTINS_ECHO] = "echo";
	p_mini->builtins_name[BUILTINS_ENV] = "env";
	p_mini->builtins_name[BUILTINS_EXIT] = "exit";
	p_mini->builtins_name[BUILTINS_EXPORT] = "export";
	p_mini->builtins_name[BUILTINS_PWD] = "pwd";
	p_mini->builtins_name[BUILTINS_UNSET] = "unset";
	p_mini->builtins_name[NB_BUILTINS] = NULL;
}

static void	init_builtins_func(t_minishell *p_mini)
{
	p_mini->builtins_func[BUILTINS_CD] = &builtin_cd;
	p_mini->builtins_func[BUILTINS_ECHO] = &builtin_echo;
	p_mini->builtins_func[BUILTINS_ENV] = &builtin_env;
	p_mini->builtins_func[BUILTINS_EXPORT] = &builtin_export;
	p_mini->builtins_func[BUILTINS_EXIT] = &builtin_exit;
	p_mini->builtins_func[BUILTINS_UNSET] = &builtin_unset;
	p_mini->builtins_func[BUILTINS_PWD] = &builtin_pwd;
}
