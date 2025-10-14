/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externals_copies.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 20:28:55 by malapoug          #+#    #+#             */
/*   Updated: 2025/10/14 01:59:01 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_material	material_init(int emmissive, t_vec4 color,
		double roughness, double refraction_index)
{
	t_material	r;

	r.emmissive = emmissive;
	r.color = color;
	r.roughness = roughness;
	r.refraction_index = refraction_index;
	return (r);
}

t_object	*object_init(
		t_mat3 trans_matrix, t_vec3 offset,
		t_material material, t_vec3 b1, t_vec3 b2,
		t_hit_info (*ray_func)(t_ray)
	)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	obj->trans_matrix = trans_matrix;
	obj->offset = offset;
	obj->material = material;
	obj->ray_func = ray_func;
	obj->bounding_volume.corner1=b1;
	obj->bounding_volume.corner2=b2;
	return (obj);
}
