/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_objs_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 15:18:08 by neon-05           #+#    #+#             */
/*   Updated: 2025/10/31 16:22:11 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_object	*new_light(
	double params[7], t_object **objs, int i, int emmissive)
{
	t_object	o;

	o.offset = vec3(params[0], params[1], params[2]);
	o.trans_matrix = mat3(
			vec3(1, 0., 0.),
			vec3(0., 1, 0.),
			vec3(0., 0., 1)
			);
	o.bounding_volume.corner1 = vec3(INFINITY, INFINITY, INFINITY);
	o.bounding_volume.corner2 = vec3(-INFINITY, -INFINITY, -INFINITY);
	o.ray_func = ray_light;
	o.material = material_init(emmissive, vec4_scale(
				vec4(params[4], params[5], params[6], 1.), params[3]), 1.);
	objs[i] = object_init(o);
	objs[i + 1] = NULL;
	return (objs[i]);
}
