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

/* This function take as input:
 *	-> str : which is a string given by the user,
 *	-> and try to duplicate this string into two parts : 
 *		-> *p_new_key is the key (the part before the first '=' sign)
 *		-> *p_new_value is the value (the part after the first '=' sign)
 *		(if there is no equal sign *p_new_value is NULL,
 *		and *p_new_key is the ducplication of str)
 *	-> in case of success return (0) and have the two part correctly duplicated
 *	-> in case of failure return a non null integer 
 *	and have already malloced part freed
 * to check :
 *	-> first ft_strdup() fail : DONE -> OK !
 *	-> second ft_strdup() fail : DONE -> OK !
 *	-> third ft_strdup()fial : DONE -> OK !
*/
int	get_new_key_value(char *str, char **p_new_key, char **p_new_value)
{
	char	*equal_position;

	equal_position = ft_strchr(str, '=');
	if (equal_position == NULL)
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
			free(*p_new_key);
			return (ERROR_MALLOC);
		}
	}
	return (0);
}
