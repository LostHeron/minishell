/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:49:50 by jweber            #+#    #+#             */
/*   Updated: 2025/06/20 15:40:41 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int	builtin_cd(t_vector	args, t_minishell *p_mini);
int	get_path_len_name(char *place_to_go, size_t *p_path_len, \
													char **p_path_name);
int	builtin_cd_without_path_given(t_minishell *p_mini);
int	builtin_echo(t_vector args, t_minishell *p_mini);
int	builtin_env(t_vector args, t_minishell *p_mini);
int	builtin_export(t_vector args, t_minishell *p_mini);
int	export_from_string(char *str, t_minishell *p_mini);
int	get_new_key_value(char *str, char **p_new_key, char **p_new_value);
int	add_new_env(char *new_key, char *new_value, t_minishell *p_mini);
int	builtin_exit(t_vector args, t_minishell *p_mini);
int	builtin_pwd(t_vector args, t_minishell *p_mini);
int	builtin_unset(t_vector args, t_minishell *p_mini);

# define BUILTINS_NB 7
# define NB_BUILTINS BUILTINS_NB

enum e_builtins
{
	BUILTINS_CD = 0,
	BUILTINS_ECHO,
	BUILTINS_ENV,
	BUILTINS_EXIT,
	BUILTINS_EXPORT,
	BUILTINS_PWD,
	BUILTINS_UNSET,
};

#endif
