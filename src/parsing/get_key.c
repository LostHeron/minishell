/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:39:57 by jweber            #+#    #+#             */
/*   Updated: 2025/07/14 13:46:33 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_char.h"
#include "ft_string.h"

/* to check 
 *	-> ft_strndup fail : DONE -> OK !
*/
char	*get_key(char *line)
{
	size_t	i;
	char	*res;

	i = 0;
	while (line[i] && ft_isalnum(line[i]) != 0)
	{
		i++;
	}
	res = ft_strndup(line, i);
	return (res);
}
