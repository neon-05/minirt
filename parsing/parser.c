/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:54:48 by malapoug          #+#    #+#             */
/*   Updated: 2025/11/07 14:58:06 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	once_objects(t_parse *parse, char **tab, char *line)
{
	if (check_line(parse, tab, line) == SKIPPED)
		return (free_tab(tab), SKIPPED);
	parse->once = ft_strjoin_f(parse->once, tab[0]);
	if (!parse->once)
		return (free_tab(tab), MALLOC_ERROR);
	if (tab[0][0] == 'A' && ambiant(parse, tab, line) == SKIPPED)
		return (SKIPPED);
	else if (tab[0][0] == 'L' && light(parse, tab, line) == SKIPPED)
		return (SKIPPED);
	else if (tab[0][0] == 'C' && camera(parse, tab, line) == SKIPPED)
		return (SKIPPED);
	return (SUCCESS);
}

int	others_objects(t_parse *parse, char **tab, char *line)
{
	char	*error;

	error = RED"ERROR: "RESET;
	if (check_others(parse, tab, line) == SKIPPED)
		return (free_tab(tab), SKIPPED);
	if (tab[0][0] == 's' && tab[0][1] == 'p')
		return (sphere(parse, tab, line));
	else if (tab[0][0] == 'p' && tab[0][1] == 'l')
		return (plane(parse, tab, line));
	else if (tab[0][0] == 'c' && tab[0][1] == 'y')
		return (cylinder(parse, tab, line));
	else
		return (printf("%sUnrecognized object :\n%s\n\n", error, line)
			, free_tab(tab), SKIPPED);
	parse->n_objects++;
	return (SUCCESS);
}

int	get_data(t_parse *parse, char *line)
{
	char	**tab;
	char	*error;

	error = RED"ERROR: "RESET;
	tab = split_ispace(line);
	if (!tab)
		return (MALLOC_ERROR);
	if (!tab[0])
		return (free_tab(tab), SUCCESS);
	if (tab[0] && tab[0][0] == '#')
		return (free_tab(tab), SUCCESS);
	else if (ft_strlen(tab[0]) == 1 && ft_strchr("ACL", tab[0][0]))
		return (once_objects(parse, tab, line));
	else if (ft_strlen(tab[0]) == 2)
		return (others_objects(parse, tab, line));
	else if (tab[0])
	{
		printf("%sUnrecognized object :\n%s\n\n", error, line);
		free_tab(tab);
		return (SKIPPED);
	}
	return (SUCCESS);
}

size_t	parse(t_scene *scene, int fd)
{
	t_parse		parse;
	char		*line;
	int			status;

	init_parse(&parse);
	parse.scene = scene;
	while (get_line(&line, fd) > 0)
	{
		status = get_data(&parse, line);
		free(line);
		line = NULL;
		if (status == MALLOC_ERROR || status == SKIPPED)
			return (free_parse(&parse), status);
	}
	if (line)
		free(line);
	if (ft_strlen(parse.once) != 3 || !ft_strchr(SET, parse.once[0])
		|| !ft_strchr(SET, parse.once[1]) || !ft_strchr(SET, parse.once[2]))
		return (free_parse(&parse),
			printf("Not all the mandatory elements are here..."), SKIPPED);
	if (assign(scene, &parse) == MALLOC_ERROR)
		return (free_parse(&parse), MALLOC_ERROR);
	return (free_parse(&parse), SUCCESS);
}
