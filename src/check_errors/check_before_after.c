/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_before_after.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:24:51 by jweber            #+#    #+#             */
/*   Updated: 2025/08/06 14:56:19 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vectors.h"
#include "check_errors.h"

/* This function is called when token is one of : "|" "&&" "||"
 * should check that ((char**)token.data)[i + 1] and ((char**)token.data)[i -1]
 * exists (meaning i != tokens.size - 1 && i != 0) 
 * must check that preceding token is not one of : 
 *		"&&" "||" "|" "&" ";" ">" ">>" "<<" "<" "("
 * and that following token is not one of :
 *		"&&" "||" "|" "&" ";" ")"
 * check should be checked in function check_after
 * 
 * if it is ok : return 0
 * if it is bad token : return 1
*/
int	check_before_after(t_vector tokens, size_t i)
{
	if (check_before(tokens, i) != 0)
		return (1);
	if (check_after(tokens, i) != 0)
		return (1);
	return (0);
}
