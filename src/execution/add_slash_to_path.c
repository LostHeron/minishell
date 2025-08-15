/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_slash_to_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:50:57 by jweber            #+#    #+#             */
/*   Updated: 2025/07/17 17:51:17 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include "ft_string.h"

/* add a slash to value from PATH
 * which do not have one at their end !
 * to check
 *	-> ft_strjoin_free_first fail : DONE -> OK !
*/
int	add_slash_to_path(t_vector *p_path)
{
	size_t	len;
	size_t	i;

	i = 0;
	while (i < p_path->size)
	{
		len = ft_strlen(((char **)p_path->data)[i]);
		if (((char **)p_path->data)[i][len - 1] != '/')
		{
			((char **)p_path->data)[i] = \
ft_strjoin_free_first(((char **)p_path->data)[i], "/");
			if (((char **)p_path->data)[i] == NULL)
			{
				return (ERROR_MALLOC);
			}
		}
		i++;
	}
	return (0);
}
