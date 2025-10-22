/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsh_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neon-05 <neon-05@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:12:10 by neon-05           #+#    #+#             */
/*   Updated: 2025/10/21 17:00:54 by neon-05          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static int	random(int *seed)
{
	*seed = (*seed * LCG_MULT + LCG_INCR) & __INT_MAX__;
	return (rand());
}

t_vec3	vec3_random_normalized(int *seed)
{
	double	rand1;
	double	rand2;
	t_vec2	tmp;

	rand1 = (double) random(seed) / __INT_MAX__ * 2. * PI;
	rand2 = (double) random(seed) / __INT_MAX__ * 2. - 1.;
	tmp = vec2(cos(rand1), sin(rand2));
	return (vec2to3(vec2_scale(tmp, sqrt(1. - rand1 * rand2)), rand2));
}

double	clamp(double x)
{
	if (x > 1.)
		return (1.);
	else if (0. > x)
		return (0.);
	else
		return (x);
}

double	unsigned_max(double a, double b)
{
	if (a == -b)
		return (fmax(a, b));
	else if (fabs(a) > fabs(b))
		return (a);
	else
		return (b);
}

double	unsigned_min(double a, double b)
{
	if (a == -b)
		return (fmin(a, b));
	else if (fabs(a) < fabs(b))
		return (a);
	else
		return (b);
}
