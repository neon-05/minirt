/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 10:52:15 by malapoug          #+#    #+#             */
/*   Updated: 2025/06/23 17:45:52 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

static int	get_data(t_val *val, t_scene *scene, char *line)
{
	val->xyz = ft_split(val->tab[1], ',');
	if (arr_size(val->xyz) != 3)
		return (printf("%sCamera position has wrong number\
 of arguments:\n%s\n\n", val->error, line), SKIPPED);
	if (!val->xyz)
		return (MALLOC_ERROR);
	val->x = ft_atoi(val->xyz[0]);
	val->y = ft_atoi(val->xyz[1]);
	val->z = ft_atoi(val->xyz[2]);
	val->orient = ft_split(val->tab[2], ',');
	if (!val->orient)
		return (MALLOC_ERROR);
	if (arr_size(val->orient) != 3)
		return (printf("%sCamera orientaion has wrong number\
 of arguments :\n%s\n\n", val->error, line), SKIPPED);
	val->aa = atod(val->orient[0]);
	val->ab = atod(val->orient[1]);
	val->ac = atod(val->orient[2]);
	if (check_numbers(val, line) == SKIPPED)
		return (SKIPPED);
	if (check_ranges(val, line) == SKIPPED)
		return (SKIPPED);
	scene->cam->orientation = quaternion(val->aa, val->ab, val->ac, 0);
	scene->cam->pos = vec3(val->x, val->y, val->z);
	return (SUCCESS);
}

int	camera(t_scene *scene, char **tab, char *line)
{
	t_val	val;

	val.error = RED"ERROR: "RESET;
	val.tab = tab;
	if (get_data(&val, scene, line) == SKIPPED)
		return (SKIPPED);
	if (!is_number(tab[3]))
		return (printf("%sCamera fov has non numerics arguments\
 :\n%s\n\n", val.error, line), SKIPPED);
	scene->cam->fov_dist = atod(tab[3]);
	if (!(scene->cam->fov_dist > 0 && scene->cam->fov_dist <= 180))
		return (printf("%sCamera fov is not in the range [0 - 180]\
 :\n%s\n\n", val.error, line), SKIPPED);
	scene->cam->fov_dist = cos(scene->cam->fov_dist / 2.);
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
