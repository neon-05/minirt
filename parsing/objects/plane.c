/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:52:33 by malapoug          #+#    #+#             */
/*   Updated: 2025/10/31 16:28:36 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static int	check_ranges(t_val *val, char *line)
{
	if (val->aa < -1 || val->aa > 1 || val->ab < -1
		|| val->ab > 1 || val->ac < -1 || val->ac > 1)
		return (printf("%sPlane vector is not in the range [-1 - 1]\
 :\n%s\n\n", val->error, line), SKIPPED);
	if (val->r < 0 || val->r > 255 || val->g < 0
		|| val->g > 255 || val->b < 0 || val->b > 255)
		return (printf("%sPlane color is not in the range [0 - 255]\
 :\n%s\n\n", val->error, line), SKIPPED);
	return (SUCCESS);
}

static int	check_numbers(t_val *val, char *line)
{
	if (!is_number(val->xyz[0]) || !is_number(val->xyz[1])
		|| !is_number(val->xyz[2]))
		return (printf("%sPlane position has non numerics arguments\
 :\n%s\n\n", val->error, line), SKIPPED);
	if (!is_number(val->orient[0]) || !is_number(val->orient[1])
		|| !is_number(val->orient[2]))
		return (printf("%sPlane vector has non numerics arguments\
 :\n%s\n\n", val->error, line), SKIPPED);
	if (!is_number(val->colors[0]) || !is_number(val->colors[1])
		|| !is_number(val->colors[2]))
		return (printf("%sPlane color has non numerics arguments\
 :\n%s\n\n", val->error, line), SKIPPED);
	return (SUCCESS);
}

static int	get_data(t_val *val, char *line)
{
	int	ret;

	ret = split_assign_position(val, "Plane", 1, line);
	if (ret != SUCCESS)
		return (ret);
	ret = split_assign_vector(val, "Plane", 2, line);
	if (ret != SUCCESS)
		return (ret);
	ret = split_assign_colors(val, "Plane", 3, line);
	if (ret != SUCCESS)
		return (ret);
	if (check_numbers(val, line) == SKIPPED)
		return (SKIPPED);
	if (check_ranges(val, line) == SKIPPED)
		return (SKIPPED);
	return (SUCCESS);
}

int	plane(t_parse *parse, char **tab, char *line)
{
	t_val	*val;
	t_val	*tmp;

	val = malloc(sizeof(t_val));
	if (!val)
		return (SKIPPED);
	init_val(val);
	tmp = parse->objects;
	if (!tmp)
		parse->objects = val;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = val;
	}
	val->type = "Pl";
	val->error = RED"ERROR: "RESET;
	val->tab = tab;
	if (get_data(val, line) == SKIPPED)
		return (SKIPPED);
	colors(val, val->ratio);
	return (SUCCESS);
}
