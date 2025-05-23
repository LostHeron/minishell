/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:39:55 by jweber            #+#    #+#             */
/*   Updated: 2025/05/16 11:29:32 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define WHITE_SPACES " \t\n\v\f\r"

/*
typedef struct s_ast
{
	void	*value;
	void	*left;
	void	*right;
}	t_ast;
*/

# define ERROR_MALLOC -3
# define ERROR_UNCLOSED_S_QUOTES -10
# define ERROR_UNCLOSED_D_QUOTES -11
# define ERROR_UNCLOSED_PARENTHESIS -12

#endif
