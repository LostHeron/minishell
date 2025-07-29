/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:58:31 by jweber            #+#    #+#             */
/*   Updated: 2025/07/18 11:05:17 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "minishell.h"
#include "ft_vectors.h"
#include "parsing.h"
#include "ft_io.h"
#include "handle_signal.h"
#include "ft_standard.h"
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	get_line(t_minishell *p_mini, char **p_line, int *p_ret);
static void	init_args(char **p_args);
static char	*get_prompt(t_minishell *p_mini);

/* This fuction will readline with getline function
 * Then parse this line to transform it to tokens 
 * (in which p_tokens->data is a char ** containing the differents
 * tokens)
 * then it will free the line read.
 * to check
 *	-> get_line fail (with ret) : DONE -> OK !
 *	-> ft_split_args fail : DONE -> OK !
*/
int	line_to_tokens(t_minishell *p_mini, t_vector *p_tokens)
{
	char	*line;
	int		ret;
	char	*args[11];

	get_line(p_mini, &line, &ret);
	if (ret != 0)
		return (ret);
	if (g_my_signal != 0)
		return (0);
	if (line == NULL)
	{
		p_mini->should_exit = TRUE;
		return (1);
	}
	if (line && *line)
		add_history(line);
	init_args(args);
	ret = ft_split_args(p_tokens, line, args);
	free(line);
	return (ret);
}

/* to check
 *	-> get_prompt_fail : DONE -> OK ;
 *	-> *p_line = NULL and *p_ret != 0 : DONE -> OK !
 *	-> readline = NULL : DONE -> OK !
*/
static void	get_line(t_minishell *p_mini, char **p_line, int *p_ret)
{
	char	*prompt;

	*p_ret = 0;
	prompt = get_prompt(p_mini);
	if (prompt == NULL)
	{
		*p_ret = ERROR_MALLOC;
		return ;
	}
	if (isatty(0) == 1)
	{
		*p_line = readline(prompt);
		free(prompt);
		if (g_my_signal != 0)
		{
			return ;
		}
	}
	else
	{
		free(prompt);
		*p_line = get_next_line(0, p_ret);
		return ;
	}
}

static void	init_args(char **p_args)
{
	p_args[0] = "&&";
	p_args[1] = "||";
	p_args[2] = "<<";
	p_args[3] = ">>";
	p_args[4] = "|";
	p_args[5] = ">";
	p_args[6] = "<";
	p_args[7] = "(";
	p_args[8] = ")";
	p_args[9] = NULL;
}

static void	free_line(t_vector *ptr_vec);

/* This function should return a pointer to the malloced
 * prompt. 
 *	In case of failure : it should have 
 *	freed all memory allocated in this function
 *	and return NULL
 *	In case of success : return a pointer to the malloced prompt 
*/
static char	*get_prompt(t_minishell *p_mini)
{
	int			ret;
	t_vector	line;
	char		*nb;

	ret = ft_vector_init(&line, 20, sizeof(char), &free_line);
	if (ret != 0)
		return (NULL);
	ret = ft_vector_add_multi(&line,
			p_mini->cwd_name, ft_strlen(p_mini->cwd_name));
	if (ret != 0)
	{
		ft_vector_free(&line);
		return (NULL);
	}
	ret = ft_vector_add_multi(&line, " [ ", 3);
	if (ret != 0)
	{
		ft_vector_free(&line);
		return (NULL);
	}
	nb = ft_itoa(p_mini->last_error_code);
	if (nb == NULL)
	{
		ft_vector_free(&line);
		return (NULL);
	}
	ret = ft_vector_add_multi(&line, nb, ft_strlen(nb));
	free(nb);
	if (ret != 0)
	{
		ft_vector_free(&line);
		return (NULL);
	}
	ret = ft_vector_add_multi(&line, " ]$ \0", 5);
	if (ret != 0)
	{
		ft_vector_free(&line);
		return (NULL);
	}
	return (line.data);
}

static void	free_line(t_vector *ptr_vec)
{
	ptr_vec->size = 0;
	free(ptr_vec->data);
	ptr_vec->data = NULL;
}
