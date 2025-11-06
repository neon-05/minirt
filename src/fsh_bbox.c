/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsh_bbox.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neon-05 <neon-05@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:11:33 by neon-05           #+#    #+#             */
/*   Updated: 2025/10/21 16:25:55 by neon-05          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	format_bbox(t_vec3 *v1, t_vec3 *v2)
{
	t_vec3	c1;
	t_vec3	c2;

	c1 = vec3(
			unsigned_min(v1->x, v2->x),
			unsigned_min(v1->y, v2->y),
			unsigned_min(v1->z, v2->z)
			);
	c2 = vec3(
			unsigned_max(v1->x, v2->x),
			unsigned_max(v1->y, v2->y),
			unsigned_max(v1->z, v2->z)
			);
	*v1 = c1;
	*v2 = c2;
}

int	check_2d_box(t_vec2 min, t_vec2 max, t_vec2 dir)
{
	double	b1x;
	double	b2y;
	int		r;

	r = (min.y * max.y < 0.) + ((min.x * max.x < 0.) << 1);
	if (r == 3)
		return (1);
	if (r & 1)
		b1x = min.x;
	else
		b1x = max.x;
	if (r & 2)
		b2y = min.y;
	else
		b2y = max.y;
	return ((dir.x * min.y < dir.y * b1x) ^ ((dir.x * b2y < dir.y * min.x)));
}

int	check_bounding_vol(t_bound_vol box, t_ray ray)
{
	int		s;
	t_vec3	c1;
	t_vec3	c2;

	c1 = vec3_sub(box.corner1, ray.origin);
	c2 = vec3_sub(box.corner2, ray.origin);
	format_bbox(&c1, &c2);
	s = 1;
	s &= check_2d_box(vec2(c1.x, c1.y), vec2(c2.x, c2.y),
			vec2(ray.n_director.x, ray.n_director.y));
	s &= check_2d_box(vec2(c1.y, c1.z), vec2(c2.y, c2.z),
			vec2(ray.n_director.y, ray.n_director.z));
	s &= check_2d_box(vec2(c1.z, c1.x), vec2(c2.z, c2.x),
			vec2(ray.n_director.z, ray.n_director.x));
	return (s);
}
