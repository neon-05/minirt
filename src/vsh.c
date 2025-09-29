#include "../minirt.h"

int	check_bounding_vol(t_bound_vol box, t_ray ray);

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
		if (check_bounding_vol(scene->objects[i]->bounding_volume, ray))
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

t_vec4	calculate_color_mix(t_scene *scene, t_hit_info hit, t_vec3 hit_direction, int depth)
{
	int		i;
	t_ray	ray;
	t_vec4	col;
	t_vec3	spec_dir;

	i = 0;
	ray.origin = hit.point;
	col = vec4(0., 0., 0., 0.);
	spec_dir = vec3_scale(q_rot(hit_direction, vec3to4(hit.normal, 0.)), -1.);
	do
	{
		ray.n_director = vec3_lerp(vec3_normalize(vec3_add(hit.normal, vec3_random_normalized())), spec_dir, hit.object->material.roughness);
		col = vec4_add(col, get_ray_color(scene, ray, depth - 1));
	}
	while (hit.object->material.roughness > .1 && i++ < RAY_PER_BOUNCE);
	col = vec4_scale(col, 1./RAY_PER_BOUNCE);
	return (vec4_cwmul(col, hit.object->material.color));
}

int	check_2d_box(t_vec2 min, t_vec2 max, t_vec2 dir)
{
	double	b1x;
	double	b2y;
	int		r;

	r = (min.y * max.y < 0.) + ((min.x * max.x < 0.) << 1);
	if (r == 3)
		return 1;
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

double	unsigned_max(double a, double b)
{
	if (a == -b)
		return (fmax(a,b));
	else if (fabs(a) > fabs(b))
		return(a);
	else
		return (b);
}

double	unsigned_min(double a, double b)
{
	if (a == -b)
		return (fmin(a,b));
	else if (fabs(a) < fabs(b))
		return(a);
	else
		return (b);
}

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

int	check_bounding_vol(t_bound_vol box, t_ray ray)
{
	int	s;

	t_vec3	c1;
	t_vec3	c2;

	c1 = vec3_sub(box.corner1, ray.origin);
	c2 = vec3_sub(box.corner2, ray.origin);
	
	format_bbox(&c1, &c2);

	s = 1;
	s &= check_2d_box(vec2(c1.x, c1.y), vec2(c2.x, c2.y), vec2(ray.n_director.x, ray.n_director.y));
	s &= check_2d_box(vec2(c1.y, c1.z), vec2(c2.y, c2.z), vec2(ray.n_director.y, ray.n_director.z));
	s &= check_2d_box(vec2(c1.z, c1.x), vec2(c2.z, c2.x), vec2(ray.n_director.z, ray.n_director.x));

	return (s);
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
		col = calculate_color_mix(scene, hit, ray.n_director, depth);
		col.w /= hit.distance * LIGHT_ATTENUATION;
		return (col);
	}
}

void	vertex_shader(t_scene *scene, t_vec4 *frag_color, t_vec2 uv)
{
	t_ray	ray;
	t_vec4	col;

	ray.origin = scene->cam->pos;
	ray.n_director = q_rot(vec3_normalize(vec2to3(uv, scene->cam->fov_dist)), scene->cam->orientation);
	col = vec4_lerp(*frag_color, get_ray_color(scene, ray, RAY_DEPTH_LIMIT), clamp(frag_color->w));
	*frag_color = col;
}
