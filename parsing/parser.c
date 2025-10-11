/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:54:48 by malapoug          #+#    #+#             */
/*   Updated: 2025/10/12 01:47:56 by malapoug         ###   ########.fr       */
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
		return (free_tab(tab), SKIPPED);
	else if (tab[0][0] == 'L' && light(parse, tab, line) == SKIPPED)
		return (free_tab(tab), SKIPPED);
	else if (tab[0][0] == 'C' && camera(parse, tab, line) == SKIPPED)
		return (free_tab(tab), SKIPPED);
	return (free_tab(tab), SUCCESS);
}

int	others_objects(t_parse *parse, char **tab, char *line)
{
	if (check_others(parse, tab, line) == SKIPPED)
		return (free_tab(tab), SKIPPED);
	if (tab[0][0] == 's' && tab[0][1] == 'p' &&
			sphere(parse, tab, line) == SKIPPED)
		return (free_tab(tab), SKIPPED);
	else if (tab[0][0] == 'p' &&
			tab[0][1] == 'l' && plane(parse, tab, line) == SKIPPED)
		return (free_tab(tab), SKIPPED);
	else if (tab[0][0] == 'c' && tab[0][1] == 'y' &&
			cylinder(parse, tab, line) == SKIPPED)
		return (free_tab(tab), SKIPPED);
	parse->n_objects++;
	return (free_tab(tab), SUCCESS);
}

int	get_data(t_parse *parse, char *line)
{
	char	**tab;
	char	*error;

	error = RED"ERROR: "RESET;
	tab = split_ispace(line);
	if (!tab)
		return (MALLOC_ERROR);
	if (!(arr_size(tab) >= 3 && arr_size(tab) <= 6))
		return (free_tab(tab), SUCCESS);
	if (ft_strlen(tab[0]) == 1 && ft_strchr("ACL", tab[0][0]))
		return (once_objects(parse, tab, line));
	else if (ft_strlen(tab[0]) == 2 && tab[0][0] == '/' && tab[0][1] == '/')
		return (free_tab(tab), SUCCESS);
	else if (ft_strlen(tab[0]) == 2)
		return (others_objects(parse, tab, line));
	else
	{
		printf("%sUnrecognized object :\n%s\n\n", error, line);
		free_tab(tab);
		return (SKIPPED);
	}
	return (SUCCESS);
}

void	init_parse(t_parse *parse)
{
	parse->once = NULL;
	parse->scene = NULL;
	parse->camera = NULL;
	parse->ambiant = NULL;
	parse->light = NULL;
	parse->objects = NULL;
}

size_t	parse(t_scene *scene, int fd)//n of line parsed ?
{
	t_parse		parse;
	char		*line;
	int			status;

	init_parse(&parse);
	parse.scene = scene;
	while (get_line(&line, fd))
	{
		status = get_data(&parse, line);
		free(line);
		if (status == MALLOC_ERROR)
			return (free_parse(&parse), MALLOC_ERROR);
		else if (status == SKIPPED)
			return (free_parse(&parse), SKIPPED);
	}
	if (line)
		free(line);
	show_parse(parse);
	// assign(scene, parse);
	return (free_parse(&parse), SUCCESS);
}

//if line not valid skipp, add 1 to return value

// R resolution int int

/*

scene->objects[0] = 
object_init(mat3_scale(i_mat3i, 1./30.), vec3(10., 40., -20.), material_init(1, vec4(1., 1., 1., 1.), 1., 1.), vec3(100.,100.,100.), vec3(-100.,-100.,-100.), ray_sphere);
										 offset				   material_init(emmissive, vec4(RGBA),roughness,refraction_index) , b1, b2,              t_hit_info (*ray_func)(t_ray)

*/
