/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_real_delimiter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:21:04 by jweber            #+#    #+#             */
/*   Updated: 2025/07/14 17:13:42 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_standard.h"
#include "ft_string.h"
#include "minishell.h"
#include <stddef.h>
#include <unistd.h>

static int	handle_quote_i(char **p_delimiter, char **p_final_delimiter,
				size_t *p_i);
static int	concatenate_outside_quote(char **p_final_delimiter,
				char **p_delimiter, size_t *p_i);
static int	case_encounter_quote(char **p_final_delimiter,
				char **p_delimiter, size_t *p_i);
static int	case_not_empty_quote(char **p_final_delimiter,
				char **p_delimiter, size_t *p_i);

/* to check
 *	-> ft_calloc fail : DONE -> OK !
 *	-> concatenate_outside_quote fail : DONE -> OK !
 *	-> case_encounter_quotes fail : DONE -> OK !
*/
char	*get_real_delimiter(char *delimiter)
{
	size_t	i;
	char	*final_delimiter;
	int		ret;

	i = 0;
	final_delimiter = ft_calloc(1, sizeof(char));
	if (final_delimiter == NULL)
		return (NULL);
	while (delimiter[i])
	{
		ret = handle_quote_i(&delimiter, &final_delimiter, &i);
		if (ret != 0)
			return (NULL);
	}
	return (final_delimiter);
}

static int	handle_quote_i(char **p_delimiter, char **p_final_delimiter,
				size_t *p_i)
{
	int	ret;

	while ((*p_delimiter)[*p_i] && (*p_delimiter)[*p_i] != '\''
		&& (*p_delimiter)[*p_i] != '\"')
		(*p_i)++;
	if (*p_i != 0)
	{
		ret = concatenate_outside_quote(p_final_delimiter, p_delimiter, p_i);
		if (ret != 0)
			return (ret);
	}
	if ((*p_delimiter)[*p_i])
	{
		ret = case_encounter_quote(p_final_delimiter, p_delimiter, p_i);
		if (ret != 0)
			return (ret);
	}
	return (0);
}

/* to check
 *	-> ft_strndup fail : DONE -> OK !
 *	-> ft_strjoin_free_first : DONE -> OK !
*/
static int	concatenate_outside_quote(char **p_final_delimiter,
				char **p_delimiter, size_t *p_i)
{
	char	*tmp_string;

	tmp_string = ft_strndup(*p_delimiter, *p_i);
	if (tmp_string == NULL)
	{
		free(*p_final_delimiter);
		return (ERROR_MALLOC);
	}
	*p_final_delimiter = ft_strjoin_free_first(*p_final_delimiter, \
tmp_string);
	free(tmp_string);
	if (*p_final_delimiter == 0)
		return (ERROR_MALLOC);
	*p_delimiter += *p_i;
	*p_i = 0;
	return (0);
}

/* to check
 *	-> case_not_empty fail : DONE -> OK !
*/
static int	case_encounter_quote(char **p_final_delimiter,
				char **p_delimiter, size_t *p_i)
{
	char	quote_type;
	int		ret;

	quote_type = (*p_delimiter)[*p_i];
	(*p_delimiter)++;
	while ((*p_delimiter)[*p_i] && (*p_delimiter)[*p_i] != quote_type)
		(*p_i)++;
	if ((*p_i) != 0)
	{
		ret = case_not_empty_quote(p_final_delimiter, p_delimiter, p_i);
		if (ret != 0)
			return (ret);
	}
	else
		(*p_delimiter)++;
	return (0);
}

/* to check
 *	-> ft_strndup fail : DONE -> OK !
 *	-> ft_strjoin_free_first : DONE -> OK !
*/
static int	case_not_empty_quote(char **p_final_delimiter,
				char **p_delimiter, size_t *p_i)
{
	char	*tmp_string;

	tmp_string = ft_strndup(*p_delimiter, *p_i);
	if (tmp_string == NULL)
	{
		free(*p_final_delimiter);
		return (ERROR_MALLOC);
	}
	*p_final_delimiter = ft_strjoin_free_first(*p_final_delimiter,
			tmp_string);
	free(tmp_string);
	if (*p_final_delimiter == 0)
		return (ERROR_MALLOC);
	*p_delimiter += *p_i + 1;
	*p_i = 0;
	return (0);
}
