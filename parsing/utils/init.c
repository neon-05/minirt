/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 17:17:37 by malapoug          #+#    #+#             */
/*   Updated: 2025/11/03 17:10:32 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	init_parse(t_parse *parse)
{
	parse->once = NULL;
	parse->scene = NULL;
	parse->camera = NULL;
	parse->ambiant = NULL;
	parse->light = NULL;
	parse->objects = NULL;
}

void	init_val(t_val *v)
{
	v->tab = NULL;
	v->colors = NULL;
	v->xyz = NULL;
	v->orient = NULL;
	v->type = NULL;
	v->error = NULL;
	v->next = NULL;
	v->r = 0;
	v->g = 0;
	v->b = 0;
	v->ratio = 1;
	v->teta = 0;
	v->x = 0;
	v->y = 0;
	v->z = 0;
	v->aa = 0;
	v->ab = 0;
	v->ac = 0;
	v->fov = 0;
	v->diametre = 0;
	v->height = 0;
}
