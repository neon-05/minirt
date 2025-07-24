#include "../minirt.h"

double	mat2_det(t_mat2 m)
{
	return (m.l1.x * m.l2.y - m.l1.y * m.l2.x);
}

double	mat3_det(t_mat3 m)
{
	t_mat2	subm1;
	t_mat2	subm2;
	t_mat2	subm3;

	subm1 = mat2(vec2(m.l2.y, m.l2.z), vec2(m.l3.y, m.l3.z));
	subm2 = mat2(vec2(m.l2.x, m.l2.z), vec2(m.l3.x, m.l3.z));
	subm3 = mat2(vec2(m.l2.x, m.l2.y), vec2(m.l3.x, m.l3.y));
	return (m.l1.x * mat2_det(subm1) - m.l1.y * mat2_det(subm2) + m.l1.z * mat2_det(subm3));
}

t_mat3	mat3_inverse(t_mat3 m)
{
	return (mat3_scale(mat3_trans(m), 1./mat3_det(m)));
}

static t_hit_info	calculate_ray(t_scene *scene, t_ray ray)
{
	t_hit_info	hit_info;
	t_hit_info	tmp_hit_info;
	size_t		i;
	t_ray		new_ray;

	i = 0;
	hit_info.object = NULL;
	hit_info.distance = -1.;
	while (scene->objects[i])
	{
		new_ray.origin = vec3_sub(mat3_mul_vec3(scene->objects[i]->trans_matrix,ray.origin), scene->objects[i]->offset);
		new_ray.n_director = vec3_normalize(mat3_mul_vec3(scene->objects[i]->trans_matrix, ray.n_director));
		//new_ray.origin = vec3_sub(ray.origin, scene->objects[i]->offset);
		//new_ray.n_director = ray.n_director;
		tmp_hit_info = scene->objects[i]->ray_func(new_ray);
		if (0. < tmp_hit_info.distance && (hit_info.distance < 0. || tmp_hit_info.distance < hit_info.distance))
		{
			hit_info = tmp_hit_info;
			if (0. < tmp_hit_info.distance)
				hit_info.object = scene->objects[i];
		}
		i++;
	}
	if (hit_info.object)
		hit_info.normal = vec3_normalize(mat3_mul_vec3((hit_info.object->trans_matrix), hit_info.normal));
	return (hit_info);
}

static t_vec3	vec3_random_normalized()
{
	double	rand1;
	double	rand2;
	t_vec2	tmp;

	rand1 = (double) rand() / RAND_MAX * 2 * PI;
	rand2 = (double) rand() / RAND_MAX * 2. - 1.;

	tmp = vec2(cos(rand1), sin(rand2));
	return (vec2to3(vec2_scale(tmp, sqrt(1. - rand1 * rand2)), rand2));
}

t_vec4 vertex_shader(t_scene *scene, t_vec2 uv)
{
	size_t	bounces;
	t_ray	ray;
	t_hit_info	h;
	double		m;

	bounces = 0;
	ray.origin = scene->cam->pos;
	ray.n_director = q_rot(vec3_normalize(vec2to3(uv, scene->cam->fov_dist)), scene->cam->orientation);
	ray.strength = 1.;
	while (bounces++ < RAY_DEPTH_LIMIT)
	{
		h = calculate_ray(scene, ray);
		if (h.object && h.object->material.emmissive)
			break;
		ray.origin = vec3_add(ray.origin, vec3_scale(ray.n_director, h.distance));
		ray.n_director = vec3_random_normalized();
	}
	m = clamp(vec3_dot(h.normal, vec3(0., 1., 0.)));
	if (h.object)
		return (vec4_scale(h.object->material.color, (h.object->material.emmissive) ? 1. : m));
	else
		return (scene->ambient);
}
