/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 21:34:07 by malapoug          #+#    #+#             */
/*   Updated: 2025/10/21 15:36:54 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	assign_cam(t_scene *scene, t_parse *parse)
{
	t_val	*tmp;

	tmp = parse->camera;
	// printf("%f, %f, %f, %f, %f, %f, %f \n\n", tmp->x, tmp->y, tmp->z, tmp->aa, tmp->ab, tmp->ac, tmp->fov);
	scene->cam->pos = vec3(tmp->x, tmp->y, tmp->z);
	scene->cam->orientation = vec4(tmp->aa, tmp->ab, tmp->ac, 0); // je mets quoi en dernier argument la ??
	scene->cam->fov_dist = (WIN_WIDTH / WIN_HEIGHT) / tan((tmp->fov * PI / 180.0) / 2.0);
}

int	assign_obj(t_scene *scene, t_val *obj, int i)
{
	//printf("%s, %f, %f, %f, %f, %f, %f, %f, %f \n\n", obj->type, obj->x, obj->y, obj->z, obj->aa, obj->ab, obj->ac, obj->diametre, obj->height);
	if (obj->type[0] == 'L' || (obj->type[0] == 'S' && obj->type[1] == 'p'))
		new_obj("sp", (double []){obj->x, obj->y, obj->z, obj->diametre/2, obj->r, obj->g, obj->b},
			scene->objects, i);
	else if (obj->type[0] == 'P' && obj->type[1] == 'l' )
		new_obj("pl", (double []){obj->x, obj->y, obj->z, obj->aa, obj->ab,
			obj->ac, obj->r, obj->g, obj->b}, scene->objects, i);
	else if (obj->type[0] == 'C' && obj->type[1] == 'y' )
		new_obj("cy", (double []){obj->x, obj->y, obj->z, obj->aa, obj->ab,
			obj->ac, obj->diametre, obj->height, obj->r, obj->g, obj->b}, scene->objects, i);
	else if (obj->type[0] == 'C' && obj->type[1] == 'u' )
		new_obj("cu", (double []){obj->x, obj->y, obj->z, obj->diametre, obj->r, obj->g, obj->b}, scene->objects, i);
	return (SUCCESS);
}

int	ft_lst(t_val *lst)
{
	int	count;

	if (!lst)
		return (0);
	count = 1;
	while (lst->next)
	{
		count += 1;
		lst = lst->next;
	}
	return (count);
}

int	assign(t_scene *scene, t_parse *parse)
{
	t_val	*tmp;
	int		i;

	tmp = parse->objects;
	i = ft_lst(tmp);
	scene->objects = malloc(sizeof(t_object) * (i + 1));
	if (!scene->objects)
		return (MALLOC_ERROR);
	scene->objects[i + 1] = NULL;
	assign_cam(scene, parse);
	scene->ambient = colors(parse->ambiant, parse->ambiant->ratio);
	while (tmp)
	{
		if (assign_obj(scene, tmp, i) == MALLOC_ERROR)
			return (MALLOC_ERROR); // free
		tmp = tmp->next;
	}
	return (SUCCESS);
}
