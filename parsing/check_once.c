/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_once.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:52:55 by malapoug          #+#    #+#             */
/*   Updated: 2025/06/23 17:53:54 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_number(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '.' && str[i] != '\n' && \
			(str[i] != '+' && i != 0) && (str[i] != '-' && i != 0))
			return (0);
		i++;
	}
	return (1);
}

int	check_line(t_parse *parse, char **tab, char *line)
{
	char	*error;

	error = RED"ERROR: "RESET;
	if (ft_strchr(parse->once, tab[0][0]))
		return (printf("%sUnothorized duplicated object :\n%s\n\n"\
			, error, line), SKIPPED);
	if (tab[0][0] == 'A' && arr_size(tab) != 3)
		return (printf("%sAmbiant light has wrong number of arguments :\n%s\n\n"\
			, error, line), SKIPPED);
	else if (tab[0][0] == 'C' && arr_size(tab) != 4)
		return (printf("%sCamera has wrong number of arguments :\n%s\n\n"\
			, error, line), SKIPPED);
	else if (tab[0][0] == 'L' && arr_size(tab) != 4)
		return (printf("%sLight has wrong number of arguments :\n%s\n\n"\
			, error, line), SKIPPED);
	else if (check_others(parse, tab, line) == SKIPPED)
		return (SKIPPED);
	return (SUCCESS);
}
