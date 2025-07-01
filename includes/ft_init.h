/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:39:05 by jweber            #+#    #+#             */
/*   Updated: 2025/07/01 17:40:02 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_INIT_H
# define FT_INIT_H

# include "minishell.h"

void	init_builtins(t_minishell *p_mini);
int		init_env(t_minishell *p_mini, char **env);
int		init_minishell(t_minishell *p_mini, char **env);

#endif
