/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_dist_functions_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 15:11:03 by neon-05           #+#    #+#             */
/*   Updated: 2025/10/31 16:21:43 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_hit_info	ray_light(t_ray ray)
{
	t_hit_info	ret;

	ret.distance = -vec3_dot(ray.origin, ray.origin)
		/ vec3_dot(ray.origin, ray.n_director);
	if (ret.distance <= 0.)
		return (ret);
	ret.point = vec3_add(
			ray.origin, vec3_scale(ray.n_director, ret.distance)
			);
	if (vec3_dot(ret.point, ret.point) > vec3_dot(ray.origin, ray.origin))
		ret.distance = -1.;
	ret.normal = ray.origin;
	return (ret);
}
