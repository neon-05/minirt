/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 21:34:07 by malapoug          #+#    #+#             */
/*   Updated: 2025/11/06 23:45:29 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	assign_cam(t_scene *scene, t_parse *parse)
{
	t_val	*tmp;

	tmp = parse->camera;
	scene->cam->pos = vec3(tmp->x, tmp->y, tmp->z);
	if (val->aa != val->ab != 0 && val->ac != -1)
		scene->cam->orientation = vec3to4(vec3_normalize(
					vec3_lerp(vec3(0, 0, 1),
						vec3(tmp->aa, tmp->ab, tmp->ac), 0.5)), 0.);
	else
		scene->cam->orientation = vec3to4(vec3_normalize(
					vec3(0, 0, 1)), 0.);
	scene->cam->passes = 0;
	scene->cam->fov_dist = (WIN_WIDTH / WIN_HEIGHT)
		/ tan((tmp->fov * PI / 180.0) / 2.0);
}

int	assign_obj(t_scene *scene, t_val *obj)
{
	if (ft_strncmp("Sp", obj->type, 3) == 0)
		new_obj("sp", (double []){obj->x, obj->y, obj->z, obj->diametre / 2,
			obj->r, obj->g, obj->b}, scene->objects, 0);
	else if (ft_strncmp("Pl", obj->type, 3) == 0)
		new_obj("pl", (double []){obj->x, obj->y, obj->z, obj->aa, obj->ab,
			obj->ac, obj->r, obj->g, obj->b}, scene->objects, 0);
	else if (ft_strncmp("Cy", obj->type, 3) == 0)
		new_obj("cy", (double []){obj->x, obj->y, obj->z, obj->aa, obj->ab,
			obj->ac, obj->diametre, obj->height, obj->r,
			obj->g, obj->b}, scene->objects, 0);
	return (SUCCESS);
}

int	ft_lst(t_val *lst)
{
	int	count;

	if (!lst)
		return (0);
	count = 0;
	while (lst)
	{
		count += 1;
		if (ft_strncmp(lst->type, "Cy", 2) == 0)
			count += 2;
		lst = lst->next;
	}
	return (count);
}

int	assign(t_scene *scene, t_parse *parse)
{
	t_val	*tmp;
	int		i;

	tmp = parse->objects;
	scene->objects = malloc(sizeof(t_object) * ((ft_lst(tmp) + 1) + 1));
	if (!scene->objects)
		return (MALLOC_ERROR);
	i = -1;
	while (++i < ft_lst(tmp) + 1)
		scene->objects[i] = NULL;
	assign_cam(scene, parse);
	scene->ambient = colors(parse->ambiant, parse->ambiant->ratio);
	new_obj("L", (double []){parse->light->x, parse->light->y,
		parse->light->z, parse->light->ratio,
		parse->light->r, parse->light->g, parse->light->b}, scene->objects, 1);
	while (tmp)
	{
		if (assign_obj(scene, tmp) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
