/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt_hd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:11:13 by jweber            #+#    #+#             */
/*   Updated: 2025/08/14 16:11:45 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*get_prompt_hd(char *delimiter)
{
	char	*new_line;

	new_line = ft_strjoin("hd (", delimiter);
	if (new_line == NULL)
		return (new_line);
	new_line = ft_strjoin_free_first(new_line, ") >");
	if (new_line == NULL)
		return (new_line);
	return (new_line);
}
