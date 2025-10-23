/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neon-05 <neon-05@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:29:40 by ylabussi          #+#    #+#             */
/*   Updated: 2025/10/23 23:19:27 by neon-05          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static void	*malloc_e(int n, int *e);
static int	alloc_mlx(t_scene *scene);

static void	*malloc_e(int n, int *e)
{
	void	*ptr;

	if (*e)
		ptr = NULL;
	else
	{
		ptr = malloc(n);
		*e |= !ptr;
	}
	return (ptr);
}

static void	free_c(void **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}

void	free_all(t_scene *scene)
{
	if (scene->cam->img)
		mlx_destroy_image(scene->mlx, scene->cam->img);
	if (scene->window)
		mlx_destroy_window(scene->mlx, scene->window);
	if (scene->mlx)
		mlx_destroy_display(scene->mlx);
	free_c((void **) &scene->mlx);
	free_c((void **) &scene->cam->prev_frame);
	free_c((void **) &scene->cam);
	free_obj_arr(scene->objects);
	free_c((void **) &scene);
}

static int	alloc_mlx(t_scene *scene)
{
	int	err;

	err = 0;
	scene->mlx = mlx_init();
	if (!scene->mlx)
		err = 1;
	else
	{
		scene->window = mlx_new_window(
				scene->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE
				);
		if (!scene->window)
			err = 1;
		else
		{
			scene->cam->img = mlx_new_image(scene->mlx, WIN_WIDTH, WIN_HEIGHT);
			if (!scene->cam->img)
				err = 1;
		}
	}
	return (err);
}

int	alloc_all(t_scene **scene)
{
	t_scene	*ret;
	int		err;

	err = 0;
	ret = malloc_e(sizeof(t_scene), &err);
	ret->cam = malloc_e(sizeof(t_cam), &err);
	ret->cam->prev_frame = malloc_e(
			sizeof(t_vec4) * WIN_HEIGHT * WIN_WIDTH, &err
			);
	ret->cam->passes = 0;
	err |= alloc_mlx(ret);
	if (err)
		free_all(ret);
	*scene = ret;
	return (err);
}
