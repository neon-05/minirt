/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externals_copies.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 20:28:55 by malapoug          #+#    #+#             */
/*   Updated: 2025/10/14 16:04:45 by malapoug         ###   ########.fr       */
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


t_hit_info	ray_sphere(t_ray ray)
{
	t_hit_info	ret;
	double	d1;
	double	d2;
	t_vec3	p2;

	d1 = -vec3_dot(ray.n_director, ray.origin);
	p2 = vec3_add(ray.origin, vec3_scale(ray.n_director, d1));
	d2 = vec3_dot(p2, p2);
	if (d2 > 1.)
		ret.distance = -1.;
	else
		ret.distance = d1 - sqrt(1. - d2);
	if (ret.distance > 0.)
	{
		ret.point = vec3_add(ray.origin, vec3_scale(ray.n_director, ret.distance));
		ret.normal = ret.point;
	}
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
			ret.point = vec3_add(ray.origin, vec3_scale(ray.n_director, ret.distance));
	}
	else
		ret.distance = -1.;
	return (ret);
}
