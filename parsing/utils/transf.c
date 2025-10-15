/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:42:06 by malapoug          #+#    #+#             */
/*   Updated: 2025/10/14 15:19:58 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_vec4	colors(t_val *val, double a)
{
	static double	inv_range = 1.0f * (1. / 255.);

	val->r = val->r * inv_range;
	val->g = val->g * inv_range;
	val->b = val->b * inv_range;
	return (vec4(val->r, val->g, val->b, a));
}

t_vec4	quaternion(double a, double b, double c, double teta)
{
	double		length;
	double		sa;
	double		ca;

	length = sqrt(a * a + b * b + c * c);
	if (length == 0.0)
		length = 1.0;
	a /= length;
	b /= length;
	c /= length;
	sa = sin(teta / 2.0);
	ca = cos(teta / 2.0);
	return (vec4(a * sa, b * sa, c * sa, ca));
}
