/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:48:43 by jweber            #+#    #+#             */
/*   Updated: 2025/08/08 16:15:05 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_standard.h"
#include "ft_string.h"
#include <errno.h>
#include <stdio.h>

static char	*get_str(char *begin, char *file, char *function, int line);
static char	*get_str_start(char *begin, char *file, char *function);

int	ft_perror(char *begin, char *file, char *function, int line)
{
	int		err_code;
	int		new_err_code;
	char	*str;

	err_code = errno;
	str = get_str(begin, file, function, line);
	if (str == NULL)
	{
		new_err_code = 0;
		errno = err_code;
		perror(begin);
		errno = new_err_code;
		perror("malloc");
		return (err_code);
	}
	errno = err_code;
	perror(str);
	free(str);
	return (err_code);
}

static char	*get_str(char *begin, char *file, char *function, int line)
{
	char	*str;
	char	*str_nb;

	str = get_str_start(begin, file, function);
	if (str == NULL)
		return (NULL);
	str_nb = ft_itoa(line);
	if (str_nb == NULL)
	{
		free(str);
		return (NULL);
	}
	str = ft_strjoin_free_first(str, str_nb);
	free(str_nb);
	return (str);
}

static char	*get_str_start(char *begin, char *file, char *function)
{
	char	*str;

	str = ft_strjoin(begin, ": from function `");
	if (str == NULL)
		return (NULL);
	str = ft_strjoin_free_first(str, function);
	if (str == NULL)
		return (NULL);
	str = ft_strjoin_free_first(str, "' in ");
	if (str == NULL)
		return (NULL);
	str = ft_strjoin_free_first(str, file);
	if (str == NULL)
		return (NULL);
	str = ft_strjoin_free_first(str, " at line:");
	return (str);
}
