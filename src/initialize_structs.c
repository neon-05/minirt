/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_structs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neon-05 <neon-05@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:38:09 by ylabussi          #+#    #+#             */
/*   Updated: 2025/10/21 16:23:43 by neon-05          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

t_object	*object_init(t_object o)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	*obj = o;
	obj->_inv_trans_matrix = mat3_inverse(o.trans_matrix);
	return (obj);
}
