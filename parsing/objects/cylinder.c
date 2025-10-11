/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:52:33 by malapoug          #+#    #+#             */
/*   Updated: 2025/06/25 13:43:47 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static int	check_ranges(t_val *val, char *line)
{
	if (val->aa < -1 || val->aa > 1 || val->ab < -1 \
		|| val->ab > 1 || val->ac < -1 || val->ac > 1)
		return (printf("%sCylinder vector is not in the range [-1 - 1]\
 :\n%s\n\n", val->error, line), SKIPPED);
	if (val->r < 0 || val->r > 255 || val->g < 0 \
		|| val->g > 255 || val->b < 0 || val->b > 255)
		return (printf("%sCylinder color is not in the range [0 - 255]\
 :\n%s\n\n", val->error, line), SKIPPED);
	return (SUCCESS);
}

static int	check_numbers(t_val *val, char *line)
{
	if (!is_number(val->xyz[0]) || !is_number(val->xyz[1]) || \
		!is_number(val->xyz[2]))
		return (printf("%sCylinder position has non numerics arguments\
 :\n%s\n\n", val->error, line), SKIPPED);
	if (!is_number(val->orient[0]) || !is_number(val->orient[1]) || \
		!is_number(val->orient[2]))
		return (printf("%sCylinder vector has non numerics arguments\
 :\n%s\n\n", val->error, line), SKIPPED);
	if (!is_number(val->tab[3]))
		return (printf("%sCylinder diametre is not numeric :\n%s\n\n"\
			, val->error, line), SKIPPED);
	if (!is_number(val->tab[4]))
		return (printf("%sCylinder height is not numeric :\n%s\n\n"\
			, val->error, line), SKIPPED);
	if (!is_number(val->colors[0]) || !is_number(val->colors[1]) || \
		!is_number(val->colors[2]))
		return (printf("%sCylinder color has non numerics arguments\
 :\n%s\n\n", val->error, line), SKIPPED);
	return (SUCCESS);
}

static int	get_data(t_val *val, t_scene *scene, char *line)
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
	(void)scene;
	return (SUCCESS);
}

// void	assign(t_scene *scene, t_val *val)
// {
	// // object[last] to do
	// scene->objects[0] = object_init(mat3_scale(i_mat3i, 1./30.), vec3(val->x, val->y, val->z), material_init(1, colors(&val, val->ratio), 1., 1.), vec3(100.,100.,100.), vec3(-100.,-100.,-100.), ray_cylinder);
// }

int	cylinder(t_scene *scene, char **tab, char *line)
{
	t_val	val;

	val.xyz = NULL;
	val.orient = NULL;
	val.colors = NULL;
	val.error = RED"ERROR: "RESET;
	val.tab = tab;
	if (get_data(&val, scene, line) == SKIPPED)
		return (SKIPPED);
	// assign(scene, &val);
	// c'est normal de ne pas avoir les valeures transformees ici: la fonction colors est appelee dans assign
	printf(YELLOW"cy\t %.2f,%.2f,%.2f \t %.2f,%.2f,%.2f \t %.2f \t %.2f \t %.2f,%.2f,%.2f \n"RESET, val.x, val.y, val.z, val.aa, val.ab, val.ac, val.diametre, val.height, val.r, val.g, val.b);
	free_val(&val);
	return (SUCCESS);
}

// scene->objects[0] = object_init(mat3_scale(i_mat3i, 1./30.), vec3(10., 40., -20.), material_init(1, vec4(1., 1., 1., 1.), 1., 1.), vec3(100.,100.,100.), vec3(-100.,-100.,-100.), ray_sphere);
										//					 offset				   material_init(emmissive, vec4(RGBA,roughness,refraction_index) , b1, b2,              t_hit_info (*ray_func)(t_ray)
