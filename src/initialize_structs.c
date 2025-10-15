#include "../minirt.h"

t_material	material_init(int emmissive, t_vec4 color,
		double roughness)
{
	t_material	r;

	r.emmissive = emmissive;
	r.color = color;
	r.roughness = roughness;
	return (r);
}

void	free_obj_arr(t_object **arr)
{
	int i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
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
