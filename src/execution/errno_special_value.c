/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errno_special_value.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 13:33:29 by jweber            #+#    #+#             */
/*   Updated: 2025/08/14 13:33:47 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

int	errno_special_value(int execve_errno)
{
	if (execve_errno == EACCES || execve_errno == ENOTDIR)
		return (126);
	else
		return (127);
}
