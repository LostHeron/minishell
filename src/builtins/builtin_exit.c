/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:35:10 by jweber            #+#    #+#             */
/*   Updated: 2025/07/14 14:54:43 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_vectors.h"
#include "ft_io.h"
#include "ft_standard.h"

static int	arguments_is_numeric(char *str);
static int	case_arguments_is_numeric(t_minishell *p_mini, t_vector args);
static int	case_arguments_not_numeric(t_minishell *p_mini);

int	builtin_exit(t_vector args, t_minishell *p_mini)
{
	int	ret;

	if (args.size < 2)
	{
		// should never enter here !
	}
	else if (args.size == 2)
	{
		p_mini->should_exit = TRUE;
		return (p_mini->last_error_code);
	}
	else if (args.size >= 3)
	{
		ret = arguments_is_numeric(((char **)args.data)[1]);
		if (ret == 0)
			return (case_arguments_is_numeric(p_mini, args));
		else
			return (case_arguments_not_numeric(p_mini));
	}
	else
	{
		// should never enter here !
	}
	return (0);
}

static int	arguments_is_numeric(char *str)
{
	int		is_numeric;
	size_t	i;

	is_numeric = FALSE;
	i = 0;
	while (str[i] && ('\t' <= str[i] && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] && ('0' <= str[i] && str[i] <= '9'))
		is_numeric = TRUE;
	while (str[i] && ('0' <= str[i] && str[i] <= '9'))
		i++;
	while (str[i] && ('\t' <= str[i] && str[i] <= '\r'))
		i++;
	if (str[i] != '\0')
		is_numeric = FALSE;
	if (is_numeric == TRUE)
		return (0);
	else
		return (1);
}

static int	case_arguments_is_numeric(t_minishell *p_mini, t_vector args)
{
	if (args.size > 3)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		p_mini->last_error_code = 1;
		return (1);
	}
	else
	{
		p_mini->should_exit = TRUE;
		p_mini->last_error_code = ft_atoi(((char **)args.data)[1]);
		return (p_mini->last_error_code);
	}
}

static int	case_arguments_not_numeric(t_minishell *p_mini)
{
	ft_putstr_fd("exit: numeric argument required\n", 2);
	p_mini->should_exit = TRUE;
	return (2);
}
