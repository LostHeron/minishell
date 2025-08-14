/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:25:25 by jweber            #+#    #+#             */
/*   Updated: 2025/08/14 16:32:21 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "handle_signal.h"
#include "ft_input.h"
#include "ft_string.h"
#include "ft_standard.h"

static int	compare_line(char *line, int *p_exiting, char *delimiter);
static int	get_line_compare(char *line, char **p_line_compare);

/* to check :
 *	-> read_the_line fail : DONE -> OK !
 *	-> compare_line fail : DONE -> OK !
 *	-> transform_write_line fail : DONE -> OK !
*/
int	rl_here_doc(t_minishell *p_mini, char **p_line, char *delimiter,
					int *p_exiting)
{
	int		ret;
	char	*prompt;

	prompt = get_prompt_hd(delimiter);
	if (prompt == NULL)
	{
		*p_exiting = 1;
		return (ERROR_MALLOC);
	}
	get_line(p_mini, p_line, &ret, prompt);
	free(prompt);
	if (ret != 0 || g_my_signal != 0)
	{
		*p_exiting = 1;
		return (ret);
	}
	if (*p_line == NULL)
	{
		*p_exiting = 1;
		return (here_doc_delimited_by_end_of_file(delimiter));
	}
	ret = compare_line(*p_line, p_exiting, delimiter);
	if (*p_exiting == 1)
		return (ret);
	return (0);
}

/* to check
 *	-> ft_strndup fail : DONE ;
*/
static int	compare_line(char *line, int *p_exiting, char *delimiter)
{
	int		ret;
	char	*line_compare;

	ret = get_line_compare(line, &line_compare);
	if (ret != 0)
		return (ret);
	ret = ft_strcmp(line_compare, delimiter);
	free(line_compare);
	if (ret == 0)
	{
		*p_exiting = 1;
		free(line);
		return (0);
	}
	return (0);
}

static int	get_line_compare(char *line, char **p_line_compare)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0)
	{
		*p_line_compare = ft_strdup(line);
		if (*p_line_compare == NULL)
			return (ERROR_MALLOC);
		if ((*p_line_compare)[len - 1] == '\n')
			(*p_line_compare)[len - 1] = '\0';
	}
	else
	{
		*p_line_compare = ft_calloc(1, sizeof(char));
		if (*p_line_compare == NULL)
			return (ERROR_MALLOC);
	}
	return (0);
}
