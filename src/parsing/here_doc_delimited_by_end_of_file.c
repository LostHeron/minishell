/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_delimited_by_end_of_file.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:40:58 by jweber            #+#    #+#             */
/*   Updated: 2025/07/14 14:50:18 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_io.h"
#include "minishell.h"

/* to check : 
 *	-> ft_srjoin fail : DONE -> OK !
 *	-> ft_strjoin_free_first fail : DONE -> OK !
 *	-> ft_putstr_fd fail : DONE -> OK !
*/
int	here_doc_delimited_by_end_of_file(char *delimiter)
{
	char	*str;
	int		nb_write;

	str = ft_strjoin(\
"warning: here-document delimited by end-of-file (wanted `", delimiter);
	if (str == NULL)
		return (ERROR_MALLOC);
	str = ft_strjoin_free_first(str, "')\n");
	if (str == NULL)
		return (ERROR_MALLOC);
	nb_write = ft_putstr_fd(str, 2);
	free(str);
	if (nb_write < 0)
		return (ERROR_WRITE);
	return (0);
}
