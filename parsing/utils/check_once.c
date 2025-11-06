/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_once.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:52:55 by malapoug          #+#    #+#             */
/*   Updated: 2025/10/31 15:55:00 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	is_number(char	*str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '.')
			count++;
		if (count > 1)
			return (0);
		if (!(ft_isdigit(str[i]) || str[i] == '.' || str[i] == '\n'
				|| (i == 0 && (str[i] == '+' || str[i] == '-'))))
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
		return (printf("%sUnothorized duplicated object :\n%s\n\n"
				, error, line), SKIPPED);
	if (tab[0][0] == 'A' && arr_size(tab) != 3)
		return (printf("%sAmbiant light has wrong number of arguments :\n%s\n\n"
				, error, line), SKIPPED);
	else if (tab[0][0] == 'C' && arr_size(tab) != 4)
		return (printf("%sCamera has wrong number of arguments :\n%s\n\n"
				, error, line), SKIPPED);
	else if (tab[0][0] == 'L' && arr_size(tab) != 4)
		return (printf("%sLight has wrong number of arguments :\n%s\n\n"
				, error, line), SKIPPED);
	else if (check_others(parse, tab, line) == SKIPPED)
		return (SKIPPED);
	return (SUCCESS);
}
