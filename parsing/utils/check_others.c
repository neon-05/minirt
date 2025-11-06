/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_others.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:10:30 by malapoug          #+#    #+#             */
/*   Updated: 2025/10/31 15:42:02 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	check_others(t_parse *parse, char **tab, char *line)
{
	char	*error;

	error = RED"ERROR: "RESET;
	if (tab[0][0] == 's' && tab[0][1] == 'p' && arr_size(tab) != 4)
		return (printf("%sSphere light has wrong number of arguments :\n%s\n\n"
				, error, line), SKIPPED);
	else if (tab[0][0] == 'p' && tab[0][1] == 'l' && arr_size(tab) != 4)
		return (printf("%sPlane has wrong number of arguments :\n%s\n\n"
				, error, line), SKIPPED);
	else if (tab[0][0] == 'c' && tab[0][1] == 'y' && arr_size(tab) != 6)
		return (printf("%sCylinlder has wrong number of arguments :\n%s\n\n"
				, error, line), SKIPPED);
	return (SUCCESS);
	(void)parse;
}
