/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:52:33 by malapoug          #+#    #+#             */
/*   Updated: 2025/06/24 03:12:06 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	check_ranges(t_val *val, char *line)
{
	if (val->aa < -1 || val->aa > 1 || val->ab < -1 \
		|| val->ab > 1 || val->ac < -1 || val->ac > 1)
		return (printf("%sPlane vector is not in the range [-1 - 1]\
 :\n%s\n\n", val->error, line), SKIPPED);
	if (val->r < 0 || val->r > 255 || val->g < 0 \
		|| val->g > 255 || val->b < 0 || val->b > 255)
		return (printf("%sPlane color is not in the range [0 - 255]\
 :\n%s\n\n", val->error, line), SKIPPED);
	return (SUCCESS);
}

static int	check_numbers(t_val *val, char *line)
{
	if (!is_number(val->xyz[0]) || !is_number(val->xyz[1]) || \
		!is_number(val->xyz[2]))
		return (printf("%sPlane position has non numerics arguments\
 :\n%s\n\n", val->error, line), SKIPPED);
	if (!is_number(val->orient[0]) || !is_number(val->orient[1]) || \
		!is_number(val->orient[2]))
		return (printf("%sPlane vector has non numerics arguments\
 :\n%s\n\n", val->error, line), SKIPPED);
	if (!is_number(val->colors[0]) || !is_number(val->colors[1]) || \
		!is_number(val->colors[2]))
		return (printf("%sPlane color has non numerics arguments\
 :\n%s\n\n", val->error, line), SKIPPED);
	return (SUCCESS);
}

static int	get_data(t_val *val, t_scene *scene, char *line)
{
	val->xyz = ft_split(val->tab[1], ',');
	if (!val->xyz)
		return (MALLOC_ERROR);
	if (arr_size(val->xyz) != 3)
		return (printf("%sPlane position has wrong number\
 of arguments:\n%s\n\n", val->error, line), SKIPPED);
	val->x = ft_atoi(val->xyz[0]);
	val->y = ft_atoi(val->xyz[1]);
	val->z = ft_atoi(val->xyz[2]);

	val->orient = ft_split(val->tab[2], ',');
	if (!val->orient)
		return (MALLOC_ERROR);
	if (arr_size(val->orient) != 3)
		return (printf("%sPlane vector has wrong number\
 of arguments:\n%s\n\n", val->error, line), SKIPPED);
	val->aa = ft_atoi(val->xyz[0]);
	val->ab = ft_atoi(val->xyz[1]);
	val->ac = ft_atoi(val->xyz[2]);

	val->colors = ft_split(val->tab[3], ',');
	if (!val->colors)
		return (MALLOC_ERROR);
	if (arr_size(val->colors) != 3)
		return (printf("%sPlane color has wrong number\
 of arguments :\n%s\n\n", val->error, line), SKIPPED);
	val->r = atod(val->colors[0]);
	val->g = atod(val->colors[1]);
	val->b = atod(val->colors[2]);
	if (check_numbers(val, line) == SKIPPED)
		return (SKIPPED);
	if (check_ranges(val, line) == SKIPPED)
		return (SKIPPED);
	(void)scene; //missing light in the scene
	return (SUCCESS);
}

int	plane(t_scene *scene, char **tab, char *line)
{
	t_val	val;

	val.error = RED"ERROR: "RESET;
	val.tab = tab;
	if (get_data(&val, scene, line) == SKIPPED)
		return (SKIPPED);
	(void)scene;
	return (SUCCESS);
}
