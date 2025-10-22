/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_objs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neon-05 <neon-05@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:05:05 by neon-05           #+#    #+#             */
/*   Updated: 2025/10/22 22:23:51 by neon-05          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static t_object	*new_sphere(
	double params[7], t_object **objs, int i, int emmissive)
{
	t_object	o;

	o.offset = vec3(params[0], params[1], params[2]);
	o.trans_matrix = mat3(
			vec3(params[3], 0., 0.),
			vec3(0., params[3], 0.),
			vec3(0., 0., params[3])
			);
	o.bounding_volume.corner1 = vec3_add(o.offset,
			vec3(params[3], params[3], params[3]));
	o.bounding_volume.corner2 = vec3_sub(o.offset,
			vec3(params[3], params[3], params[3]));
	o.ray_func = ray_sphere;
	o.material = material_init(emmissive,
			vec4(params[4], params[5], params[6], 1.), 1.);
	objs[i] = object_init(o);
	objs[i + 1] = NULL;
	return (objs[i]);
}

static t_object	*new_plane(
	double params[9], t_object **objs, int i, int emmissive)
{
	t_object	o;

	o.offset = vec3(params[0], params[1], params[2]);
	o.trans_matrix = mat3(
			vec3(0., 0., 0.),
			vec3(params[3], params[4], params[5]),
			vec3(0., 0., 0.)
			);
	if (fabs(params[4]) == 1.)
		o.trans_matrix.l1 = vec3(1., 0., 0.);
	else
		o.trans_matrix.l1 = vec3_normalize(
				vec3_cross(o.trans_matrix.l2, vec3(0., 1., 0.)));
	o.trans_matrix.l3 = vec3_cross(o.trans_matrix.l1, o.trans_matrix.l2);
	o.bounding_volume.corner1 = vec3(INFINITY, INFINITY, INFINITY);
	o.bounding_volume.corner2 = vec3(-INFINITY, -INFINITY, -INFINITY);
	o.ray_func = ray_plane;
	o.material = material_init(emmissive,
			vec4(params[6], params[7], params[8], 1.), 1.);
	objs[i] = object_init(o);
	objs[i + 1] = NULL;
	return (objs[i]);
}

static t_object	*new_cyl_cap(t_object **objs, int i)
{
	objs[i] = object_init(*(objs[i - 1]));
	if (!objs[i])
		return (NULL);
	objs[i]->offset = vec3_add(objs[i]->offset, objs[i]->trans_matrix.l2);
	objs[i]->ray_func = ray_plane_circle;
	objs[i + 1] = object_init(*(objs[i - 1]));
	if (!objs[i])
		return (NULL);
	objs[i + 1]->trans_matrix = mat3_scale(objs[i + 1]->trans_matrix, -1.);
	objs[i + 1]->_inv_trans_matrix = mat3_inverse(objs[i + 1]->trans_matrix);
	objs[i + 1]->offset = vec3_add(objs[i + 1]->offset,
			objs[i + 1]->trans_matrix.l2);
	objs[i + 1]->ray_func = ray_plane_circle;
	return (objs[i]);
}

static t_object	*new_cyl(
	double params[11], t_object **objs, int i, int emmissive)
{
	t_object	*o;
	t_mat3		m;

	m = mat3(
			vec3(params[6] * .5, 0., 0.),
			vec3(0., params[7] * .5, 0.),
			vec3(0., 0., params[6] * .5)
			);
	o = new_plane(params, objs, i, emmissive);
	o->material.color = vec4(params[8], params[9], params[10], 1.);
	o->trans_matrix = mat3_mul(m, o->trans_matrix);
	o->_inv_trans_matrix = mat3_inverse(o->trans_matrix);
	o->ray_func = ray_cylinder_bound;
	new_cyl_cap(objs, i + 1);
	objs[i + 3] = NULL;
	return (objs[i]);
}

int	new_obj(const char *id, double *params, t_object **objs, int emmissive)
{
	t_object	*o;
	int			i;

	i = 0;
	while (objs[i])
		i++;
	if (ft_strncmp(id, "sp", 3) == 0)
		o = new_sphere(params, objs, i, emmissive);
	else if (ft_strncmp(id, "pl", 3) == 0)
		o = new_plane(params, objs, i, emmissive);
	else if (ft_strncmp(id, "cy", 3) == 0)
		o = new_cyl(params, objs, i, emmissive);
	else
		return (1);
	return (!o);
}
