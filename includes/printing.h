/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:39:58 by jweber            #+#    #+#             */
/*   Updated: 2025/06/03 16:30:36 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTING_H
# define PRINTING_H

# include "minishell.h"

void	print_error(int err_code);
void	print_path(t_minishell *p_mini);
void	print_env(t_minishell *p_mini);

#endif // !PRINTING_H
