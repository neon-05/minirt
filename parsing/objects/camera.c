/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 10:52:15 by malapoug          #+#    #+#             */
/*   Updated: 2025/06/25 13:43:19 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static int	check_ranges(t_val *val, char *line)
{
	if (val->aa < -1 || val->aa > 1 || val->ab < -1 \
		|| val->ab > 1 || val->ac < -1 || val->ac > 1)
		return (printf("%sCamera orientaion is not in the range [-1 - 1]\
 :\n%s\n\n", val->error, line), SKIPPED);
	return (SUCCESS);
}

static int	check_numbers(t_val *val, char *line)
{
	if (!is_number(val->xyz[0]) || !is_number(val->xyz[1]) || \
		!is_number(val->xyz[2]))
		return (printf("%sCamera position has non numerics arguments\
 :\n%s\n\n", val->error, line), SKIPPED);
	if (!is_number(val->orient[0]) || !is_number(val->orient[1]) || \
		!is_number(val->orient[2]))
		return (printf("%sCamera orientation has non numerics arguments\
 :\n%s\n\n", val->error, line), SKIPPED);
	if (!is_number(val->orient[0]))
		return (printf("%sCamera fov has non numerics arguments\
 :\n%s\n\n", val->error, line), SKIPPED);
	return (SUCCESS);
}

static int	get_data(t_val *val, char *line)
{
	int	ret;

	ret = split_assign_position(val, "Camera", 1, line);
	if (ret != SUCCESS)
		return (ret);
	ret = split_assign_vector(val, "Camera", 2, line);
	if (ret != SUCCESS)
		return (ret);
	val->ratio = atod(val->tab[3]);
	if (check_numbers(val, line) == SKIPPED)
		return (SKIPPED);
	if (check_ranges(val, line) == SKIPPED)
		return (SKIPPED);
	return (SUCCESS);
}

int	camera(t_parse *parse, char **tab, char *line)
{
	t_val	*val;

	val = malloc(sizeof(t_val));
	if (!val)
		return (SKIPPED); // voir comment faire pour changer en MALLOC)ERROR ou si on laisse comme ca meme si c'est pas entierement accurate du coup
	val->xyz = NULL;
	val->orient = NULL;
	val->colors = NULL;
	val->error = RED"ERROR: "RESET;
	val->tab = tab;
	if (get_data(val, line) == SKIPPED)
		return (SKIPPED);
	if (!is_number(tab[3]))
		return (printf("%sCamera fov has non numerics arguments\
 :\n%s\n\n", val->error, line), SKIPPED);
	val->fov = atod(tab[3]);
	if (!(val->fov > 0 && val->fov <= 180))
		return (printf("%sCamera fov is not in the range [0 - 180]\
 :\n%s\n\n", val->error, line), SKIPPED);
	parse->camera = val;
	return (SUCCESS);
}

/*
typedef struct s_cam
{
	t_vec3	pos;
	t_vec4	orientation;
	t_mat3	model_view_matrix;		????????????
	double	fov_dist;
}	t_cam;
*/
