/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 11:54:14 by jweber            #+#    #+#             */
/*   Updated: 2025/08/06 10:34:59 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_INPUT_H
# define FT_INPUT_H

# include "minishell.h"

int		rl_gnl(char **p_line, char *prompt);
char	*get_prompt(t_minishell *p_mini);
void	get_line(t_minishell *p_mini, char **p_line, int *p_ret, char *prompt);

#endif
