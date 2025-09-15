#include "../minirt.h"

static void	replace_hit_info(t_object *obj, t_hit_info *cur_hit, t_ray ray)
{
	t_hit_info	hit_info;
	t_hit_info	tmp_hit_info;
	t_ray		new_ray;

	new_ray.origin = mat3_mul_vec3(obj->trans_matrix, vec3_sub(ray.origin, obj->offset));
	new_ray.n_director = vec3_normalize(mat3_mul_vec3(obj->trans_matrix, ray.n_director));
	tmp_hit_info = obj->ray_func(new_ray);
	if (0. < tmp_hit_info.distance)
	{
		hit_info.point = vec3_add(mat3_mul_vec3(obj->_inv_trans_matrix, tmp_hit_info.point), obj->offset);
		hit_info.distance = vec3_distance(ray.origin, hit_info.point);
		if (cur_hit->distance <= 0. || hit_info.distance < cur_hit->distance)
		{
			hit_info.object = obj;
			hit_info.normal = tmp_hit_info.normal;
			*cur_hit = hit_info;
		}
	}
}

static t_hit_info	calculate_ray(t_scene *scene, t_ray ray)
{
	t_hit_info	hit_info;
	size_t		i;

	i = 0;
	hit_info.object = NULL;
	hit_info.distance = -1.;
	while (scene->objects[i])
	{
		replace_hit_info(scene->objects[i], &hit_info, ray);
		i++;
	}
	if (hit_info.object)
		hit_info.normal = vec3_normalize(mat3_mul_vec3(hit_info.object->trans_matrix, hit_info.normal));
	return (hit_info);
}

static t_vec3	vec3_random_normalized()
{
	double	rand1;
	double	rand2;
	t_vec2	tmp;

	rand1 = (double) rand() / RAND_MAX * 2. * PI;
	rand2 = (double) rand() / RAND_MAX * 2. - 1.;

	tmp = vec2(cos(rand1), sin(rand2));
	return (vec2to3(vec2_scale(tmp, sqrt(1. - rand1 * rand2)), rand2));
}

t_vec4	get_ray_color(t_scene *scene, t_ray ray, int depth);

t_vec4	calculate_color_mix(t_scene *scene, t_hit_info hit, int depth)
{
	int		i;
	t_ray	ray;
	t_vec4	col;

	i = 0;
	ray.origin = hit.point;
	col = vec4(0., 0., 0., 0.);
	while (i++ < RAY_PER_BOUNCE)
	{
		ray.n_director = vec3_normalize(vec3_add(hit.normal, vec3_random_normalized()));
		col = vec4_add(col, get_ray_color(scene, ray, depth - 1));
	}
	col = vec4_scale(col, 1./RAY_PER_BOUNCE);
	return (vec4_cwmul(col, hit.object->material.color));
}

t_vec4	get_ray_color(t_scene *scene, t_ray ray, int depth)
{
	t_hit_info	hit;
	t_vec4		col;

	hit = calculate_ray(scene, ray);
	if (!hit.object || depth <= 0)
		return (scene->ambient);
	else if (hit.object->material.emmissive)
		return (hit.object->material.color);
	else
	{
		col = calculate_color_mix(scene, hit, depth);
		col.w = 0.;
		return (col);
	}
}

t_vec4 vertex_shader(t_scene *scene, t_vec2 uv)
{
	size_t	bounces;
	t_ray	ray;
	t_vec4	col;

	bounces = 0;
	ray.origin = scene->cam->pos;
	ray.n_director = q_rot(vec3_normalize(vec2to3(uv, scene->cam->fov_dist)), scene->cam->orientation);
	col = get_ray_color(scene, ray, RAY_DEPTH_LIMIT);

	return (col);
}
