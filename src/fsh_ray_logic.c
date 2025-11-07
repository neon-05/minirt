/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsh_ray_logic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:06:46 by ylabussi          #+#    #+#             */
/*   Updated: 2025/11/05 16:33:31 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int		check_bounding_vol(t_bound_vol box, t_ray ray);
t_vec4	get_ray_color(t_scene *scene, t_ray ray, int depth);

static void	replace_hit_info(
	t_object *obj, t_hit_info *cur_hit, t_ray ray, int depth)
{
	t_hit_info	hit_info;
	t_hit_info	tmp_hit_info;
	t_ray		new_ray;

	if (depth == RAY_DEPTH_LIMIT && obj->ray_func == ray_light)
		return ;
	new_ray.origin = mat3_mul_vec3(obj->_inv_trans_matrix,
			vec3_sub(ray.origin, obj->offset));
	new_ray.n_director = vec3_normalize(
			mat3_mul_vec3(obj->_inv_trans_matrix, ray.n_director)
			);
	tmp_hit_info = obj->ray_func(new_ray);
	if (0. < tmp_hit_info.distance)
	{
		hit_info.point = vec3_add(
				mat3_mul_vec3(obj->trans_matrix, tmp_hit_info.point),
				obj->offset);
		hit_info.distance = vec3_distance(ray.origin, hit_info.point);
		if (cur_hit->distance <= 0. || hit_info.distance < cur_hit->distance)
		{
			hit_info.object = obj;
			hit_info.normal = tmp_hit_info.normal;
			*cur_hit = hit_info;
		}
	}
}

static t_hit_info	calculate_ray(t_scene *scene, t_ray ray, int depth)
{
	t_hit_info	hit_info;
	size_t		i;

	i = 0;
	hit_info.object = NULL;
	hit_info.distance = -1.;
	while (scene->objects[i])
	{
		if (check_bounding_vol(scene->objects[i]->bounding_volume, ray))
			replace_hit_info(scene->objects[i], &hit_info, ray, depth);
		i++;
	}
	if (hit_info.object)
		hit_info.normal = vec3_normalize(mat3_mul_vec3(
					hit_info.object->_inv_trans_matrix, hit_info.normal
					));
	return (hit_info);
}

t_vec4	calculate_color_mix(
		t_scene *scene,
		t_hit_info hit,
		t_vec3 hit_direction,
		int depth)
{
	int		i;
	t_ray	ray;
	t_vec4	col;
	t_vec3	spec_dir;

	i = 0;
	ray.origin = hit.point;
	col = vec4(0., 0., 0., 0.);
	spec_dir = vec3_scale(q_rot(hit_direction, vec3to4(hit.normal, 0.)), -1.);
	while ((i == 0 || i < RAY_PER_BOUNCE)
		&& hit.object->material.roughness > .1)
	{
		ray.n_director = vec3_lerp(vec3_add(hit.normal, vec3_random_normalized(
						&scene->lcg_seed)),
				spec_dir,
				hit.object->material.roughness
				);
		col = vec4_add(col, get_ray_color(scene, ray, depth - 1));
		i++;
	}
	if (i > 0)
		col = vec4_scale(col, 1. / i);
	return (vec4_cwmul(col, hit.object->material.color));
}

t_vec4	get_ray_color(t_scene *scene, t_ray ray, int depth)
{
	t_hit_info	hit;
	t_vec4		col;

	hit = calculate_ray(scene, ray, depth);
	if (!hit.object || depth <= 0)
		return (scene->ambient);
	else if (hit.object->material.emmissive)
		return (hit.object->material.color);
	else
	{
		col = calculate_color_mix(scene, hit, ray.n_director, depth);
		return (col);
	}
}

void	fragment_shader(t_scene *scene, t_vec4 *frag_color, t_vec2 uv)
{
	t_ray	ray;
	t_vec4	col;

	ray.origin = scene->cam->pos;
	ray.n_director = q_rot(
			vec2to3(uv, scene->cam->fov_dist), scene->cam->orientation);
	col = vec4_lerp(*frag_color, get_ray_color(scene, ray, RAY_DEPTH_LIMIT),
			(double) scene->cam->passes / (scene->cam->passes + 1.));
	*frag_color = vec4_func(col, clamp);
}
