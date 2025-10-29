/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_assign.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:21:43 by malapoug          #+#    #+#             */
/*   Updated: 2025/10/29 13:19:44 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	split_assign_colors(t_val *val, char *object, int i, char *line)
{
	val->colors = ft_split(val->tab[i], ',');
	if (!val->colors)
		return (MALLOC_ERROR);
	if (arr_size(val->colors) != 3)
		return (printf("%s%s color has wrong number\
 of arguments :\n%s\n\n", val->error, object, line), SKIPPED);
	val->r = atod(val->colors[0]);
	val->g = atod(val->colors[1]);
	val->b = atod(val->colors[2]);
	return (SUCCESS);
}

int	split_assign_vector(t_val *val, char *object, int i, char *line)
{
	val->orient = ft_split(val->tab[i], ',');
	if (!val->orient)
		return (MALLOC_ERROR);
	if (arr_size(val->orient) != 3)
		return (printf("%s%s vector has wrong number\
 of arguments:\n%s\n\n", val->error, object, line), SKIPPED);
	val->aa = atod(val->orient[0]);
	val->ab = atod(val->orient[1]);
	val->ac = atod(val->orient[2]);
	return (SUCCESS);
}

int	split_assign_position(t_val *val, char *object, int i, char *line)
{
	val->xyz = ft_split(val->tab[i], ',');
	if (!val->xyz)
		return (MALLOC_ERROR);
	if (arr_size(val->xyz) != 3)
		return (printf("%s%s position has wrong number\
 of arguments:\n%s\n\n", val->error, object, line), SKIPPED);
	val->x = atod(val->xyz[0]);
	val->y = atod(val->xyz[1]);
	val->z = atod(val->xyz[2]);
	return (SUCCESS);
}
