/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 20:28:16 by malapoug          #+#    #+#             */
/*   Updated: 2025/10/11 20:29:02 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	main(int ac, char **av)
{
	t_scene		*scene;
	int			fd;
	// t_mat3		i_mat3i;

	// i_mat3i = mat3(vec3(1., 0., 0.), vec3(0., 1., 0.), vec3(0., 0., 1.));
	scene = malloc(sizeof(t_scene));
	scene->cam = malloc(sizeof(t_cam));
	scene->objects = malloc(sizeof(t_object *) * 4);
	scene->cam->pos = vec3(0., 0., -1.);



	// scene->objects[0] = object_init(i_mat3i, vec3(0., 0., 3.), material_init(0, vec4(1., 1., 0., 1.), 1., 1.), NULL); //dist_sphere);
	// scene->objects[1] = object_init(i_mat3i, vec3(2.5, -.75, 1.), material_init(0, vec4(1., 1., 1., 1.), 1., 1.), NULL); //dist_sphere);
	// scene->objects[2] = object_init(i_mat3i, vec3(0., -1., 0.), material_init(0, vec4(1., 0., 1., 1.), 1., 1.), NULL); //dist_plane);
	// scene->objects[3] = NULL;
	fd = open("./config.rt", O_RDONLY);
	if (fd < 0)
		fd = open("parsing/config.rt", O_RDONLY);
	if (fd < 0)
		return (MALLOC_ERROR);
	parse(scene, fd);
	(void)ac;
	(void)av;
}
