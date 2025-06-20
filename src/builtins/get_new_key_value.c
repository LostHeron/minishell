/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_key_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:51:48 by jweber            #+#    #+#             */
/*   Updated: 2025/06/20 15:07:42 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_string.h"

int	get_new_key_value(char *str, char **p_new_key, char **p_new_value)
{
	char	*equal_position;

	equal_position = ft_strchr(str, '=');
	if (equal_position == NULL || equal_position[1] == '\0')
	{
		*p_new_key = ft_strdup(str);
		if (*p_new_key == NULL)
			return (ERROR_MALLOC);
		*p_new_value = NULL;
	}
	else
	{
		*p_new_key = ft_strndup(str, equal_position - str);
		if (*p_new_key == NULL)
			return (ERROR_MALLOC);
		*p_new_value = ft_strdup(equal_position + 1);
		if (*p_new_value == NULL)
		{
			free(*p_new_value);
			return (ERROR_MALLOC);
		}
	}
	return (0);
}
