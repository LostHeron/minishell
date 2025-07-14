/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_real_delimiter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:21:04 by jweber            #+#    #+#             */
/*   Updated: 2025/07/14 14:53:52 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_standard.h"
#include "ft_string.h"
#include <unistd.h>

char	*get_real_delimiter(char *delimiter)
{
	size_t	i;
	char	*final_delimiter;
	char	*tmp_string;
	char	quote_type;

	i = 0;
	final_delimiter = ft_calloc(1, sizeof(char));
	while (delimiter[i])
	{
		while (delimiter[i] && delimiter[i] != '\'' && delimiter[i] != '\"')
			i++;
		if (i != 0)
		{
			tmp_string = ft_strndup(delimiter, i);
			if (tmp_string == NULL)
			{
				free(final_delimiter);
				return (NULL);
			}
			final_delimiter = ft_strjoin_free_first(final_delimiter, \
															tmp_string);
			free(tmp_string);
			if (final_delimiter == 0)
				return (NULL);
			delimiter += i;
			i = 0;
		}
		if (delimiter[i])
		{
			quote_type = delimiter[i];
			delimiter++;
			while (delimiter[i] && delimiter[i] != quote_type)
				i++;
			if (i != 0)
			{
				tmp_string = ft_strndup(delimiter, i);
				if (tmp_string == NULL)
				{
					free(final_delimiter);
					return (NULL);
				}
				final_delimiter = ft_strjoin_free_first(final_delimiter, \
																tmp_string);
				free(tmp_string);
				if (final_delimiter == 0)
					return (NULL);
				delimiter += i + 1;
				i = 0;
			}
			else
				delimiter++;
		}
	}
	return (final_delimiter);
}
