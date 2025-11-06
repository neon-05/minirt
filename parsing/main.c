/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 20:28:16 by malapoug          #+#    #+#             */
/*   Updated: 2025/10/29 11:24:50 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	main(int ac, char **av)
{
	t_scene		*scene;
	int			fd;

	scene = malloc(sizeof(t_scene));
	scene->cam = malloc(sizeof(t_cam));
	scene->objects = malloc(sizeof(t_object *) * 4);
	scene->cam->pos = vec3(0., 0., -1.);
	fd = open("./config.rt", O_RDONLY);
	if (ac < 2)
		fd = open("parsing/config.rt", O_RDONLY);
	else
		fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (MALLOC_ERROR);
	parse(scene, fd);
}
