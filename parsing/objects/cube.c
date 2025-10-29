/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:38:14 by malapoug          #+#    #+#             */
/*   Updated: 2025/10/29 11:44:56 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static int	check_ranges(t_val *val, char *line)
{
	if (val->aa < -1 || val->aa > 1 || val->ab < -1 \
		|| val->ab > 1 || val->ac < -1 || val->ac > 1)
		return (printf("%sCube vector is not in the range [-1 - 1]\
 :\n%s\n\n", val->error, line), SKIPPED);
	if (val->r < 0 || val->r > 255 || val->g < 0 \
		|| val->g > 255 || val->b < 0 || val->b > 255)
		return (printf("%sCube color is not in the range [0 - 255]\
 :\n%s\n\n", val->error, line), SKIPPED);
	return (SUCCESS);
}

static int	check_numbers(t_val *val, char *line)
{
	if (!is_number(val->xyz[0]) || !is_number(val->xyz[1]) || \
		!is_number(val->xyz[2]))
		return (printf("%sCube position has non numerics arguments\
 :\n%s\n\n", val->error, line), SKIPPED);
	if (!is_number(val->orient[0]) || !is_number(val->orient[1]) || \
		!is_number(val->orient[2]))
		return (printf("%sCube vector has non numerics arguments\
 :\n%s\n\n", val->error, line), SKIPPED);
	if (!is_number(val->tab[3]))
		return (printf("%sCube size is not numeric :\n%s\n\n", \
			val->error, line), SKIPPED);
	if (!is_number(val->colors[0]) || !is_number(val->colors[1]) || \
		!is_number(val->colors[2]))
		return (printf("%sCube color has non numerics arguments\
 :\n%s\n\n", val->error, line), SKIPPED);
	return (SUCCESS);
}

static int	get_data(t_val *val, char *line)
{
	int	ret;

	ret = split_assign_position(val, "Cube", 1, line);
	if (ret != SUCCESS)
		return (ret);
	ret = split_assign_vector(val, "Cube", 2, line);
	if (ret != SUCCESS)
		return (ret);
	val->diametre = atod(val->tab[3]);
	ret = split_assign_colors(val, "Cube", 4, line);
	if (ret != SUCCESS)
		return (ret);
	if (check_numbers(val, line) == SKIPPED)
		return (SKIPPED);
	if (check_ranges(val, line) == SKIPPED)
		return (SKIPPED);
	return (SUCCESS);
}

int	cube(t_parse *parse, char **tab, char *line)
{
	t_val	*val;
	t_val	*tmp;

	val = malloc(sizeof(t_val));
	if (!val)
		return (SKIPPED); // voir comment faire pour changer en MALLOC)ERROR ou si on laisse comme ca meme si c'est pas entierement accurate du coup
	val->type = "Cu";
	val->xyz = NULL;
	val->orient = NULL;
	val->error = RED"ERROR: "RESET;
	val->tab = tab;
	val->next = NULL;
	if (get_data(val, line) == SKIPPED)
		return (SKIPPED);
	colors(val, val->ratio);
	tmp = parse->objects;
	if (!tmp)
		parse->objects = val;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = val;
	}
	return (SUCCESS);
}
