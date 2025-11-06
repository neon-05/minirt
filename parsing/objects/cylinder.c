/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:52:33 by malapoug          #+#    #+#             */
/*   Updated: 2025/10/31 16:29:13 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static int	check_ranges(t_val *val, char *line)
{
	if (val->aa < -1 || val->aa > 1 || val->ab < -1
		|| val->ab > 1 || val->ac < -1 || val->ac > 1)
		return (printf("%sCylinder vector is not in the range [-1 - 1]\
 :\n%s\n\n", val->error, line), SKIPPED);
	if (val->r < 0 || val->r > 255 || val->g < 0
		|| val->g > 255 || val->b < 0 || val->b > 255)
		return (printf("%sCylinder color is not in the range [0 - 255]\
 :\n%s\n\n", val->error, line), SKIPPED);
	return (SUCCESS);
}

static int	check_numbers(t_val *val, char *line)
{
	if (!is_number(val->xyz[0]) || !is_number(val->xyz[1])
		|| !is_number(val->xyz[2]))
		return (printf("%sCylinder position has non numerics arguments\
 :\n%s\n\n", val->error, line), SKIPPED);
	if (!is_number(val->orient[0]) || !is_number(val->orient[1])
		|| !is_number(val->orient[2]))
		return (printf("%sCylinder vector has non numerics arguments\
 :\n%s\n\n", val->error, line), SKIPPED);
	if (!is_number(val->tab[3]))
		return (printf("%sCylinder diametre is not numeric :\n%s\n\n"
				, val->error, line), SKIPPED);
	if (!is_number(val->tab[4]))
		return (printf("%sCylinder height is not numeric :\n%s\n\n"
				, val->error, line), SKIPPED);
	if (!is_number(val->colors[0]) || !is_number(val->colors[1])
		|| !is_number(val->colors[2]))
		return (printf("%sCylinder color has non numerics arguments\
 :\n%s\n\n", val->error, line), SKIPPED);
	return (SUCCESS);
}

static int	get_data(t_val *val, char *line)
{
	int	ret;

	ret = split_assign_position(val, "Cylinder", 1, line);
	if (ret != SUCCESS)
		return (ret);
	ret = split_assign_vector(val, "Cylinder", 2, line);
	if (ret != SUCCESS)
		return (ret);
	val->diametre = atod(val->tab[3]);
	val->height = atod(val->tab[4]);
	ret = split_assign_colors(val, "Cylinder", 5, line);
	if (ret != SUCCESS)
		return (ret);
	if (check_numbers(val, line) == SKIPPED)
		return (SKIPPED);
	if (check_ranges(val, line) == SKIPPED)
		return (SKIPPED);
	return (SUCCESS);
}

int	cylinder(t_parse *parse, char **tab, char *line)
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
	val->type = "Cy";
	val->error = RED"ERROR: "RESET;
	val->tab = tab;
	if (get_data(val, line) == SKIPPED)
		return (SKIPPED);
	colors(val, val->ratio);
	return (SUCCESS);
}
