/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:40:45 by jweber            #+#    #+#             */
/*   Updated: 2025/06/25 16:26:34 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_io.h"

void	print_error(int err_code)
{
	if (err_code == ERROR_UNCLOSED_S_QUOTES)
		ft_printf_fd(2, "syntax error : unclose single quotes\n");
	else if (err_code == ERROR_UNCLOSED_D_QUOTES)
		ft_printf_fd(2, "syntax error : unclosed double quotes\n");
	else if (err_code == ERROR_UNMATCHING_PARENTHESIS)
		ft_printf_fd(2, "syntax error : unmatching parenthesis \n");
	else if (err_code == ERROR_EMPTY_PARENTHESIS)
		ft_printf_fd(2, "syntax error : empty parenthesis \n");
}
