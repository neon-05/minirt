/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 21:34:07 by malapoug          #+#    #+#             */
/*   Updated: 2025/10/20 18:44:26 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
typedef struct s_scene
{
	t_object	**objects;
	t_cam		*cam;
	t_vec4		ambient;
	t_xvar		*mlx;
	t_win_list	*window;
}	t_scene;

typedef struct s_cam
{
	t_vec3	pos;
	t_vec4	orientation;
	t_mat3	model_view_matrix;
	t_img	*img;
	t_vec4	*prev_frame;
	double	fov_dist;
	int		passes;
	int		shift_pressed;
}	t_cam;

*/

//	scene->cam->pos = vec3(0., 0., -5.);
//	scene->cam->orientation = vec4(0., 0., 0., 1.);
//	scene->cam->fov_dist = 1.6;
//	scene->ambient = vec4(0., 0., 0., 0.);5

void	assign_cam(t_scene *scene, t_parse *parse)
{
	t_val	*tmp;

	tmp = parse->camera;
	// printf("%f, %f, %f, %f, %f, %f, %f \n\n", tmp->x, tmp->y, tmp->z, tmp->aa, tmp->ab, tmp->ac, tmp->fov);
	scene->cam->pos = vec3(tmp->x, tmp->y, tmp->z);
scene->cam->orientation = vec4(tmp->aa, tmp->ab, tmp->ac, 0); // je mets quoi en dernier argument la ??
	// scene->cam->model_view_matrix = ; // a faire
	scene->cam->fov_dist = WIN_WIDTH/WIN_HEIGHT * (tan((PI - tmp->fov) / 2));
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
	{
		new_obj("cy", (double []){obj->x, obj->y, obj->z, obj->aa, obj->ab,
			obj->ac, obj->diametre, obj->height, obj->r, obj->g, obj->b}, scene->objects, i);
	}
(void)i;
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





	t_mat3	i_mat3i = mat3(
			vec3(1., 0., 0.),
			vec3(0., 1., 0.),
			vec3(0., 0., 1.)
		);


//	scene->objects[0] = object_init(mat3_scale(i_mat3i, 1./30.), vec3(10., 40., -20.), material_init(1, vec4(1., 1., 1., 1.), 1.), vec3(100.,100.,100.), vec3(-100.,-100.,-100.), ray_sphere);
//	scene->objects[1] = object_init(i_mat3i, vec3(-1.5, 0., 0.), material_init(0, vec4(1., 1., 1., 1.), 0.), vec3(-.5,1.,1.), vec3(-2.5,-1.,-1.), ray_sphere);
//	scene->objects[2] = object_init(i_mat3i, vec3(0., 0., 3.), material_init(0, vec4(1., 1., 1., 1.), .5), vec3(3.,-1.,3.), vec3(-3.,5.,3.), ray_plane);
//	scene->objects[3] = object_init(i_mat3i, vec3(-3., 0., 0.), material_init(0, vec4(1., .5, .5, 1.), .5), vec3(-3.,-1.,3.), vec3(-3.,5.,-3.), ray_plane);
//	scene->objects[4] = object_init(i_mat3i, vec3(3., 0., 0.), material_init(0, vec4(.5, 1., .5, 1.), .5), vec3(3.,-1.,3.), vec3(3.,5.,-3.), ray_plane);
//	scene->objects[5] = object_init(i_mat3i, vec3(0., 4., 2.), material_init(1, vec4(1., 1., 1., 1.), 0.), vec3(1.,5.,1.), vec3(-1.,3.,3.), ray_sphere);
//	scene->objects[6] = object_init(i_mat3i, vec3(0., -1., 0.), material_init(0, vec4(.5, .5, 1., 1.), 1.), vec3(3.,-1.,3.), vec3(-3.,-1.,-3.), ray_plane);
//	scene->objects[7] = NULL;
(void)i_mat3i;

	return (SUCCESS);
}
