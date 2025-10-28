/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_objs_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neon-05 <neon-05@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 15:18:08 by neon-05           #+#    #+#             */
/*   Updated: 2025/10/28 23:21:19 by neon-05          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_object	*new_light(
	double params[7], t_object **objs, int i, int emmissive)
{
	t_object	o;

	o.offset = vec3(params[0], params[1], params[2]);
	o.trans_matrix = mat3(
			vec3(params[3], 0., 0.),
			vec3(0., params[3], 0.),
			vec3(0., 0., params[3])
			);
	o.bounding_volume.corner1 = vec3_add(o.offset,
			vec3(params[3], params[3], params[3]));
	o.bounding_volume.corner2 = vec3_sub(o.offset,
			vec3(params[3], params[3], params[3]));
	o.ray_func = ray_light;
	o.material = material_init(emmissive,
			vec4(params[4], params[5], params[6], 1.), 1.);
	objs[i] = object_init(o);
	objs[i + 1] = NULL;
	return (objs[i]);
}

t_object	*new_cube(
	double params[7], t_object **objs, int i, int emmissive)
{
	t_object	o;

	o.offset = vec3(params[0], params[1], params[2]);
	o.trans_matrix = mat3(
			vec3(params[3], 0., 0.),
			vec3(0., params[3], 0.),
			vec3(0., 0., params[3])
			);
	o.bounding_volume.corner1 = vec3_add(o.offset,
			vec3(params[3] / 2, params[3] / 2, params[3] / 2));
	o.bounding_volume.corner2 = vec3_sub(o.offset,
			vec3(params[3] / 2, params[3] / 2, params[3] / 2));
	o.ray_func = ray_sphere;
	o.material = material_init(emmissive, vec4(1., .5, .5, 1.), 1.);
	objs[i] = object_init(o);
	objs[i]->material.color = vec4(params[4], params[5], params[6], 1.);
	objs[i + 1] = NULL;
	return (objs[i]);
}
