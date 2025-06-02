#include "../minirt.h"

static t_hit_info	calculate_ray(t_scene *scene, t_ray ray)
{
	t_hit_info	ret;
	t_ray		new_ray;
	size_t		i;
	double		dist;

	i = 0;
	ret.distance = -1.;
	ret.object = NULL;
	while (scene->objects[i])
	{
		new_ray.origin = vec3_sub(mat3_mul_vec3(scene->objects[i]->trans_matrix, ray.origin), scene->objects[i]->offset);
		new_ray.n_director = ray.n_director;
		new_ray.strength = ray.strength;
		dist = scene->objects[i]->ray_dist_func(new_ray);
		if (dist > 0. && (dist < ret.distance || ret.distance < 0.))
		{
			ret.distance = dist;
			ret.object = scene->objects[i];
		}
		i++;
	}
	return (ret);
}

t_vec4 vertex_shader(t_scene *scene, t_vec2 uv)
{
	size_t	bounces;
	t_ray	ray;
	t_hit_info	h;

	bounces = 0;
	ray.origin = scene->cam->pos;
	ray.n_director = vec3_normalize(vec2to3(uv, scene->cam->fov_dist));
	ray.strength = 1.;
	while (bounces++ < RAY_DEPTH_LIMIT)
	{
		h = calculate_ray(scene, ray);
	}
	if (h.object)
		return (vec4_scale(h.object->material.color, 1./(h.distance+1.)));
	else
		return (scene->ambient);
}