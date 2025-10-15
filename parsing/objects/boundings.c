/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boundings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:20:33 by malapoug          #+#    #+#             */
/*   Updated: 2025/10/15 23:12:17 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

t_vec3	bbox_min_cylinder(t_val val)
{
	return (vec3(val.x - val.diametre / 2, val.y - val.height / 2, val.z - val.diametre / 2));
}

t_vec3	bbox_max_cylinder(t_val val)
{
	return (vec3(val.x + val.diametre / 2, val.y + val.height / 2, val.z + val.diametre / 2));
}

t_vec3	bbox_min_sphere(t_val val)
{
	return (vec3(val.x - val.diametre / 2, val.y - val.diametre / 2, val.z - val.diametre / 2));
}

t_vec3	bbox_max_sphere(t_val val)
{
	return (vec3(val.x + val.diametre / 2, val.y + val.diametre / 2, val.z + val.diametre / 2));
}
