/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:52:33 by malapoug          #+#    #+#             */
/*   Updated: 2025/06/24 14:41:05 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	check_ranges(t_val *val, char *line)
{
	if (val->r < 0 || val->r > 255 || val->g < 0 \
		|| val->g > 255 || val->b < 0 || val->b > 255)
		return (printf("%ssphere color is not in the range [0 - 255]\
 :\n%s\n\n", val->error, line), SKIPPED);
	return (SUCCESS);
}

static int	check_numbers(t_val *val, char *line)
{
	if (!is_number(val->xyz[0]) || !is_number(val->xyz[1]) || \
		!is_number(val->xyz[2]))
		return (printf("%sSphere position has non numerics arguments\
 :\n%s\n\n", val->error, line), SKIPPED);
	if (!is_number(val->tab[2]))
		return (printf("%sSphere ratio argument isn't numeric\
 :\n%s\n\n", val->error, line), SKIPPED);
	if (!is_number(val->colors[0]) || !is_number(val->colors[1]) || \
		!is_number(val->colors[2]))
		return (printf("%sSphere color has non numerics arguments\
 :\n%s\n\n", val->error, line), SKIPPED);
	return (SUCCESS);
}

static int	get_data(t_val *val, t_scene *scene, char *line)
{
	int	ret;

	ret = split_assign_position(val, "Sphere", 1, line);
	if (ret != SUCCESS)
		return (ret);
	val->diametre = atod(val->tab[2]);
	ret = split_assign_colors(val, "Sphere", 3, line);
	if (ret != SUCCESS)
		return (ret);
	if (check_numbers(val, line) == SKIPPED)
		return (SKIPPED);
	if (check_ranges(val, line) == SKIPPED)
		return (SKIPPED);
	(void)scene;
	return (SUCCESS);
}

int	sphere(t_scene *scene, char **tab, char *line)
{
	t_val	val;

	val.error = RED"ERROR: "RESET;
	val.tab = tab;
	if (get_data(&val, scene, line) == SKIPPED)
		return (SKIPPED);
	(void)scene;
	return (SUCCESS);
}
