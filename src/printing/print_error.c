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

static void	print_other_errors(int err_code);

void	print_error(int err_code)
{
	if (err_code == ERROR_MALLOC)
		ft_printf_fd(2, "ERROR due to memory allocation\n");
	else if (err_code == ERROR_UNCLOSED_S_QUOTES)
		ft_printf_fd(2, "syntax error : unclose single quotes\n");
	else if (err_code == ERROR_UNCLOSED_D_QUOTES)
		ft_printf_fd(2, "syntax error : unclosed double quotes\n");
	else if (err_code == ERROR_UNMATCHING_PARENTHESIS)
		ft_printf_fd(2, "syntax error : unmatching parenthesis \n");
	else if (err_code == ERROR_EMPTY_PARENTHESIS)
		ft_printf_fd(2, "syntax error : empty parenthesis \n");
	else if (err_code == ERROR_AROUND_CLOSING_PARENTHESIS)
		ft_printf_fd(2, "syntax error : error around closing parenthesis\n");
	else if (err_code == ERROR_AROUND_OPENING_PARENTHESIS)
		ft_printf_fd(2, "syntax error : error around opening parenthesis\n");
	else
		print_other_errors(err_code);
}

static void	print_other_errors(int err_code)
{
	if (err_code == ERROR_HERE_DOC_FILENAME)
		ft_printf_fd(2, \
"too much filename beginning with \"/tmp/minishell_tmp_file_nb_\"\n");
	else if (err_code == ERROR_AROUND_AND)
		ft_printf_fd(2, "syntax error : error around &&\n");
	else if (err_code == ERROR_AROUND_OR)
		ft_printf_fd(2, "syntax error : error around ||\n");
	else if (err_code == ERROR_AROUND_PIPE)
		ft_printf_fd(2, "syntax error : error around |\n");
	else if (err_code == ERROR_AROUND_BACKGROUND)
		ft_printf_fd(2, "syntax error : error around &\n");
	else if (err_code == ERROR_AROUND_SEQUENCE)
		ft_printf_fd(2, "syntax error : error around ;\n");
	else if (err_code == ERROR_AROUND_REDIR_OUT)
		ft_printf_fd(2, "syntax error : error around >\n");
	else if (err_code == ERROR_AROUND_REDIR_IN)
		ft_printf_fd(2, "syntax error : error around <\n");
	else if (err_code == ERROR_AROUND_REDIR_HEREDOC)
		ft_printf_fd(2, "syntax error : error around <<\n");
	else if (err_code == ERROR_AROUND_REDIR_APPEND)
		ft_printf_fd(2, "syntax error : error around >>\n");
	else
		ft_printf_fd(2, "syntax error : unknown error \n");
}
