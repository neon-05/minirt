/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:54:17 by malapoug          #+#    #+#             */
/*   Updated: 2025/06/24 14:27:51 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	check_ranges(t_val *val, char *line)
{
	if (!(val->ratio >= 0 && val->ratio <= 1))
		return (printf("%sLight ratio is not in the range [0.0 - 1.0]\
 :\n%s\n\n", val->error, line), SKIPPED);
	if (val->r < 0 || val->r > 255 || val->g < 0 \
		|| val->g > 255 || val->b < 0 || val->b > 255)
		return (printf("%sLight color is not in the range [0 - 255]\
 :\n%s\n\n", val->error, line), SKIPPED);
	return (SUCCESS);
}

static int	check_numbers(t_val *val, char *line)
{
	if (!is_number(val->xyz[0]) || !is_number(val->xyz[1]) || \
		!is_number(val->xyz[2]))
		return (printf("%sLight position has non numerics arguments\
 :\n%s\n\n", val->error, line), SKIPPED);
	if (!is_number(val->tab[2]))
		return (printf("%sLight ratio argument isn't numeric\
 :\n%s\n\n", val->error, line), SKIPPED);
	if (!is_number(val->colors[0]) || !is_number(val->colors[1]) || \
		!is_number(val->colors[2]))
		return (printf("%sLight color has non numerics arguments\
 :\n%s\n\n", val->error, line), SKIPPED);
	return (SUCCESS);
}

static int	get_data(t_val *val, t_scene *scene, char *line)
{
	int	ret;

	ret = split_assign_position(val, "Light", 1, line);
	if (ret != SUCCESS)
		return (ret);
	val->ratio = atod(val->tab[2]);
	ret = split_assign_colors(val, "Light", 3, line);
	if (ret != SUCCESS)
		return (ret);
	if (check_numbers(val, line) == SKIPPED)
		return (SKIPPED);
	if (check_ranges(val, line) == SKIPPED)
		return (SKIPPED);
	(void)scene; //missing light in the scene
	return (SUCCESS);
}

int	light(t_scene *scene, char **tab, char *line)
{
	t_val	val;

	val.error = RED"ERROR: "RESET;
	val.tab = tab;
	if (get_data(&val, scene, line) == SKIPPED)
		return (SKIPPED);
	(void)scene;
	return (SUCCESS);
}

//missing light in the scene
