/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:46:19 by ylabussi          #+#    #+#             */
/*   Updated: 2025/11/07 15:50:47 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	ft_endswith(const char *s, const char *ref)
{
	int	l1;
	int	l2;

	l1 = ft_strlen(s);
	l2 = ft_strlen(ref);
	if (l1 < l2)
		return (0);
	return (ft_strncmp(s + l1 - l2, ref, l2 + 1) == 0);
}

void	check_input(int cond, const char *msg, int exit_code)
{
	if (cond)
	{
		ft_putendl_fd((char *) msg, 2);
		exit(exit_code);
	}
}
