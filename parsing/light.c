/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:54:17 by malapoug          #+#    #+#             */
/*   Updated: 2025/06/25 13:43:51 by malapoug         ###   ########.fr       */
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

	val.xyz = NULL;
	val.orient = NULL;
	val.colors = NULL;
	val.error = RED"ERROR: "RESET;
	val.tab = tab;
	if (get_data(&val, scene, line) == SKIPPED)
		return (SKIPPED);
	(void)scene;
	colors(&val, val.ratio);
	printf(YELLOW"L\t %.2f,%.2f,%.2f \t %.2f \t %.2f,%.2f,%.2f \n"RESET, val.x, val.y, val.z, val.ratio, val.r, val.g, val.b);
	free_val(&val);
	return (SUCCESS);
}

//missing light in the scene
