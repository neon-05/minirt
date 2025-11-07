/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:42:06 by malapoug          #+#    #+#             */
/*   Updated: 2025/11/05 16:06:23 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_vec4	colors(t_val *val, double a)
{
	static double	inv_range = (1. / 255.);

	val->r *= inv_range * a;
	val->g *= inv_range * a;
	val->b *= inv_range * a;
	return (vec4(val->r, val->g, val->b, a));
}

t_vec4	quaternion(t_vec3 start, t_vec3 target)
{
	return (vec3to4(vec3_cross(start, target), vec3_dot(start, target)));
}
