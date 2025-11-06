/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_dist_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neon-05 <neon-05@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:02:46 by ylabussi          #+#    #+#             */
/*   Updated: 2025/10/29 19:53:32 by neon-05          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_hit_info	ray_plane_circle(t_ray ray)
{
	t_hit_info	ret;
	t_vec2		v;

	ret = ray_plane(ray);
	if (ret.distance <= 0.)
		return (ret);
	v = vec2(ret.point.x, ret.point.z);
	if (vec2_dot(v, v) > 1.)
		ret.distance = -1.;
	return (ret);
}

t_hit_info	ray_plane(t_ray ray)
{
	t_hit_info	ret;

	ret.normal = vec3(0., 1., 0.);
	if (ray.n_director.y < 0.)
	{
		ret.distance = -(ray.origin.y) / ray.n_director.y;
		if (ret.distance > 0.)
			ret.point = vec3_add(
					ray.origin, vec3_scale(ray.n_director, ret.distance)
					);
	}
	else
		ret.distance = -1.;
	return (ret);
}

t_hit_info	ray_sphere(t_ray ray)
{
	t_hit_info	ret;
	double		d1;
	double		d2;
	t_vec3		p2;

	d1 = -vec3_dot(ray.n_director, ray.origin);
	p2 = vec3_add(ray.origin, vec3_scale(ray.n_director, d1));
	d2 = vec3_dot(p2, p2);
	if (d2 > 1.)
		ret.distance = -1.;
	else
		ret.distance = d1 - sqrt(1. - d2);
	if (ret.distance > 0.)
	{
		ret.point = vec3_add(
				ray.origin, vec3_scale(ray.n_director, ret.distance)
				);
		ret.normal = ret.point;
	}
	return (ret);
}

static double	dist_ray_circle_2d(t_vec2 origin, t_vec2 dir)
{
	double	d1;
	double	d2;
	t_vec2	v2;

	d1 = -vec2_dot(origin, dir);
	v2 = vec2_add(origin, vec2_scale(dir, d1));
	d2 = vec2_dot(v2, v2);
	if (d2 < 1)
		return (d1 - sqrt(1. - d2));
	else
		return (-1);
}

t_hit_info	ray_cylinder_bound(t_ray ray)
{
	t_hit_info	ret;
	t_vec2		p1;
	t_vec2		p2;
	double		d;

	p1 = vec2(ray.origin.x, ray.origin.z);
	p2 = vec2(ray.n_director.x, ray.n_director.z);
	d = vec2_length(p2);
	ret.distance = dist_ray_circle_2d(p1, vec2_scale(p2, 1. / d)) / d;
	ret.point = vec3_add(ray.origin, vec3_scale(ray.n_director, ret.distance));
	if (fabs(ret.point.y) > 1.)
		ret.distance = -1.;
	if (ret.distance > 0.)
	{
		ret.normal = ret.point;
		ret.normal.y = 0.;
	}
	return (ret);
}
