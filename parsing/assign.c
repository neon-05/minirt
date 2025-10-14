/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 21:34:07 by malapoug          #+#    #+#             */
/*   Updated: 2025/10/14 01:59:33 by malapoug         ###   ########.fr       */
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

void	assign_cam(t_scene *scene, t_parse *parse)
{
	t_val	*tmp;

	tmp = parse->camera;
	scene->cam->pos = vec3(tmp->x, tmp->y, tmp->z);
	scene->cam->orientation = vec4(tmp->aa, tmp->ab, tmp->ac, 0); // je mets quoi en dernier argument la ??
	// scene->cam->model_view_matrix = ; // a faire
	scene->cam->fov_dist = tmp->fov;
}







t_hit_info	ray_sphere(t_ray ray)
{
	t_hit_info	ret;
	double	d1;
	double	d2;
	t_vec3	p2;

	d1 = -vec3_dot(ray.n_director, ray.origin);
	p2 = vec3_add(ray.origin, vec3_scale(ray.n_director, d1));
	d2 = vec3_dot(p2, p2);
	if (d2 > 1.)
		ret.distance = -1.;
	else
		ret.distance = d1 - sqrt(1. - d2);
	if (ret.distance > 0.)
	{
		ret.point = vec3_add(ray.origin, vec3_scale(ray.n_director, ret.distance));
		ret.normal = ret.point;
	}
	return (ret);
}










// scene->obj[i] = object_init(martix, pos, material_init(emmissive, rgba, roughness, refraction_index), border1, border2, ray_func);
int	assign_obj(t_scene *scene, t_val *obj, int i)
{
	t_vec3 pos;
	t_vec4 rgba;
	t_mat3	i_mat3i = mat3(
		vec3(1., 0., 0.),
		vec3(0., 1., 0.),
		vec3(0., 0., 1.)
	);
	
	scene->objects[i] = malloc(sizeof(t_object));
	if (!scene->objects[i])
		return (MALLOC_ERROR);

	pos = vec3(obj->x, obj->y, obj->z);
	if (obj->type[0] == 'L')
		rgba = vec4(obj->r, obj->g, obj->b, obj->ratio);
	else
		rgba = vec4(obj->r, obj->g, obj->b, 1); // je met quoi en a ?
	// matrix ?
	// emmissive ?
	// roughness ?
	// refraction_index ?
	// border1 ?
	// border2 ?
	// ray_func ?
	
	scene->objects[i] = object_init(i_mat3i, pos, material_init(1, rgba, 0.5, 0.5), vec3(100, 100, 100), vec3(100, 100, 100), ray_sphere);//change ray_func
	// scene->objects[i] = object_init(martix, pos, material_init(emmissive, rgba, roughness, refraction_index), border1, border2, ray_func);
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
	i = 0;
	while (tmp)
	{
		if (assign_obj(scene, tmp, i) == MALLOC_ERROR)
			return (MALLOC_ERROR); // free
		i++;
		tmp = tmp->next;
	}
	return (SUCCESS);
}

/*

scene->objects[4] = object_init(i_mat3ig, vec3(3., 0., 0.), material_init(0, vec4(.5, 1., .5, 1.), .5, 1.), vec3(3.,-1.,3.), vec3(3.,5.,-3.), ray_plane);
scene->objects[5] = object_init(i_mat3i, vec3(0., 4., 0.), material_init(1, vec4(1., 1., 1., 1.), 0., 1.), vec3(1.,5.,1.), vec3(-1.,3.,-1.), ray_sphere);

*/
