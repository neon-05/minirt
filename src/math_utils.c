/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neon-05 <neon-05@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:00:39 by neon-05           #+#    #+#             */
/*   Updated: 2025/10/21 16:01:22 by neon-05          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_vec4	q_mul(t_vec4 a, t_vec4 b)
{
	return (vec4(
			(a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y),
			(a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x),
			(a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w),
			(a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z)
		));
}

t_vec3	q_rot(t_vec3 v, t_vec4 q)
{
	return (vec3_add(v, vec3_scale(
				vec3_cross(vec3(q.x, q.y, q.z),
					vec3_add(vec3_cross(vec3(q.x, q.y, q.z), v),
						vec3_scale(v, q.w))), 2.)));
}

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
	return (m.l1.x * mat2_det(subm1)
		- m.l1.y * mat2_det(subm2) + m.l1.z * mat2_det(subm3));
}

t_mat3	mat3_inverse(t_mat3 m)
{
	double	d;
	t_mat3	m2;

	d = mat3_det(m);
	m2 = mat3(
			vec3(m.l2.y * m.l3.z - m.l2.z * m.l3.y,
				m.l1.z * m.l3.y - m.l1.y * m.l3.z,
				m.l1.y * m.l2.z - m.l1.z * m.l2.y),
			vec3(m.l2.z * m.l3.x - m.l2.x * m.l3.z,
				m.l1.x * m.l3.z - m.l1.z * m.l3.x,
				m.l1.z * m.l2.x - m.l1.x * m.l2.z),
			vec3(m.l2.x * m.l3.y - m.l2.y * m.l3.x,
				m.l1.y * m.l3.x - m.l1.x * m.l3.y,
				m.l1.x * m.l2.y - m.l1.y * m.l2.x)
			);
	return (mat3_scale(m2, 1. / d));
}
