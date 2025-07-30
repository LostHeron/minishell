/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:48:46 by jweber            #+#    #+#             */
/*   Updated: 2025/07/01 17:49:41 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREEING_H
# define FREEING_H

# include "minishell.h"

void		free_env(t_list *lst);
int			free_minishell(t_minishell *p_mini);

#endif
