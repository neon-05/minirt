#include "../minirt.h"

t_material	material_init(int emmissive, t_vec4 color,
		double roughness, double refraction_index
	)
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
		t_material material, double (*ray_dist_func)(t_ray)
	)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	obj->trans_matrix = trans_matrix;
	obj->offset = offset;
	obj->material = material;
	obj->ray_dist_func = ray_dist_func;
	return (obj);
}
