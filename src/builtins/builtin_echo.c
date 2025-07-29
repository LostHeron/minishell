/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:35:36 by jweber            #+#    #+#             */
/*   Updated: 2025/07/29 18:23:52 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include "minishell.h"
#include "ft_io.h"
#include <stdio.h>

static int	print_current_arg(t_vector args, size_t	i, int *p_print_new_line,
				int *p_check_for_option);
static int	is_option_n(char *str);

int	builtin_echo(t_vector args, t_minishell *p_mini)
{
	size_t	i;
	int		ret;
	int		print_new_line;
	int		check_for_option;

	i = 1;
	(void) p_mini;
	print_new_line = 1;
	check_for_option = 1;
	while (i < args.size - 1)
	{
		ret = print_current_arg(args, i, &print_new_line, &check_for_option);
		if (ret != 0)
			return (ret);
		i++;
	}
	if (print_new_line == 1)
		if (ft_printf_fd(1, "\n") < 0)
			return (ERROR_WRITE);
	return (0);
}

static int	print_current_arg(t_vector args, size_t	i, int *p_print_new_line,
								int *p_check_for_option)
{
	int	ret;

	if (*p_check_for_option == 1)
	{
		if (is_option_n(((char **)args.data)[i]) == 1)
		{
			*p_print_new_line = 0;
			return (0);
		}
	}
	*p_check_for_option = 0;
	ret = ft_printf_fd(1, "%s", ((char **)args.data)[i]);
	if (ret < 0)
		return (ERROR_WRITE);
	if (i != args.size - 2)
	{
		ret = ft_printf_fd(1, " ");
		if (ret < 0)
			return (ERROR_WRITE);
	}
	return (0);
}

/* - should return positive integer if 
 * string correspond to activate 
 * option -n of echo 
 * - should return negative integer else
*/
static int	is_option_n(char *str)
{
	size_t	i;

	i = 0;
	if (str[0] == '-')
		i++;
	else
		return (0);
	while (str[i] && str[i] == 'n')
		i++;
	if (str[i] == '\0')
		return (1);
	else
		return (0);
}
