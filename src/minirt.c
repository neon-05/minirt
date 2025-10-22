/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ylabussi <ylabussi@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/10/15 16:38:16 by ylabussi		  #+#	#+#			 */
/*   Updated: 2025/10/23 00:49:02 by malapoug         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "../minirt.h"

unsigned int	color_from_vec4(t_vec4 color)
{
	unsigned int	c;

	c = 0;
	c |= ((int)(color.w * 255.) & 0xFF) << 24;
	c |= ((int)(color.x * 255.) & 0xFF) << 16;
	c |= ((int)(color.y * 255.) & 0xFF) << 8;
	c |= ((int)(color.z * 255.) & 0xFF) << 0;
	return (c);
}

int	pixel_put_image(t_scene *scene, t_img *image, size_t pixel, t_vec4 v_color)
{
	int				pixel_bits;
	int				line_bytes;
	int				endian;
	char			*buffer;
	unsigned int	color;

	color = color_from_vec4(v_color);
	buffer = mlx_get_data_addr(image, &pixel_bits, &line_bytes, &endian);
	if (pixel_bits != 32)
		color = mlx_get_color_value(scene->mlx, color);
	if (endian)
	{
		buffer[pixel + 0] = (color >> 24);
		buffer[pixel + 1] = (color >> 16) & 0xFF;
		buffer[pixel + 2] = (color >> 8) & 0xFF;
		buffer[pixel + 3] = (color) & 0xFF;
	}
	else
	{
		buffer[pixel + 0] = (color) & 0xFF;
		buffer[pixel + 1] = (color >> 8) & 0xFF;
		buffer[pixel + 2] = (color >> 16) & 0xFF;
		buffer[pixel + 3] = (color >> 24);
	}
	return (0);
}

int	render(t_scene **scene)
{
	size_t	frag_pos;
	t_vec2	uv;

	frag_pos = 0;
	printf("\n");
	while (frag_pos < WIN_WIDTH * WIN_HEIGHT)
	{
		uv = vec2(
				(double)(frag_pos % WIN_WIDTH) / WIN_HEIGHT,
				1. - (double)(frag_pos / WIN_WIDTH) / WIN_HEIGHT
				);
		fragment_shader(*scene, &(*scene)->cam->prev_frame[frag_pos],
			vec2_sub(vec2_scale(uv, 2.),
				vec2((double) WIN_WIDTH / WIN_HEIGHT, 1.)));
		pixel_put_image(*scene, (*scene)->cam->img, frag_pos * 4,
			(*scene)->cam->prev_frame[frag_pos]);
		frag_pos++;
		printf("\033[1A\033[2Kpass %d, pixel %li/%i\n",
			(*scene)->cam->passes, frag_pos, WIN_WIDTH * WIN_HEIGHT);
	}
	(*scene)->cam->passes++;
	mlx_put_image_to_window((*scene)->mlx,
		(*scene)->window, (*scene)->cam->img, 0, 0);
	return (0);
}

int	on_key_press(int key, t_scene **scene)
{
	printf("key -p[%i]\n", key);
	if (key == KEY_ESC)
		mlx_loop_end((*scene)->mlx);
	return (0);
}

int	main(int ac, char **av)
{
	/*t_mat3	i_mat3i = mat3(
			vec3(1., 0., 0.),
			vec3(0., 1., 0.),
			vec3(0., 0., 1.)
		);

	t_mat3	i_mat3i2 = mat3(
			vec3(1., 0., 0.),
			vec3(0., 0., -1.),
			vec3(0., 1., 0.)
		);

	t_mat3	i_mat3ir = mat3(
			vec3(0., -1., 0.),
			vec3(1., 0., 0.),
			vec3(0., 0., 1.)
		);

	t_mat3	i_mat3ig = mat3(
			vec3(0., 1., 0.),
			vec3(-1., 0., 0.),
			vec3(0., 0., 1.)
		);*/
	t_scene	*scene;
//	int		err;

	if (alloc_all(&scene, 8))
		return (1);
	//scene->objects[0] = object_init((t_object) {.bounding_volume = {.corner1 = vec3(1.,1.,1.), .corner2 = vec3(-1.,-1.,-1.)}, .trans_matrix = i_mat3i, .offset = vec3(0. ,0., 0.), .material = material_init(1, vec4(1., 1., 1., 1.), 0.), .ray_func = ray_sphere});
//	err = 0;
//	err |= new_obj("sp", (double[]){0., 0., 0., 1.}, scene->objects, 8) == -1;
//	err |= new_obj("pl", (double[]){0., 0., 0., sqrt(2), 0., -sqrt(2)}, scene->objects, 8) == -1;
//	err |= new_obj("cy", (double[]){0., 2., 0., 0., 1., 0., 1., 1.}, scene->objects, 8) == -1;
//	if (err)
//	{
//		free_all(scene);
//		return (1);
//	}
	

	int fd;
	if (ac == 2)
		fd = open(av[1], O_RDONLY);
	else
		fd = open("parsing/config.rt", O_RDONLY);
	if (fd < 0)
			return (MALLOC_ERROR);
	if (parse(scene, fd) != SUCCESS)
		return 1;

/*
	scene->objects[0] = object_init(mat3_scale(i_mat3i, 30.), vec3(10., 40., -20.), material_init(1, vec4(1., 1., 1., 1.), 1.), vec3(100.,100.,100.), vec3(-100.,-100.,-100.), ray_sphere);
	scene->objects[1] = object_init(i_mat3i, vec3(0., -1., 0.), material_init(0, vec4(.5, .5, 1., 1.), 1.), vec3(3.,-1.,3.), vec3(-3.,-1.,-3.), ray_plane);
	scene->objects[2] = object_init(i_mat3i2, vec3(0., 0., 3.), material_init(0, vec4(1., 1., 1., 1.), .5), vec3(3.,-1.,3.), vec3(-3.,5.,3.), ray_plane);
	scene->objects[3] = object_init(i_mat3ir, vec3(-3., 0., 0.), material_init(0, vec4(1., .5, .5, 1.), .5), vec3(-3.,-1.,3.), vec3(-3.,5.,-3.), ray_plane);
	scene->objects[4] = object_init(i_mat3ig, vec3(3., 0., 0.), material_init(0, vec4(.5, 1., .5, 1.), .5), vec3(3.,-1.,3.), vec3(3.,5.,-3.), ray_plane);
	scene->objects[5] = object_init(i_mat3i, vec3(0., 4., 2.), material_init(1, vec4(1., 1., 1., 1.), 0.), vec3(1.,5.,1.), vec3(-1.,3.,3.), ray_sphere);
	scene->objects[6] = object_init(i_mat3i, vec3(-1.5, 0., 0.), material_init(0, vec4(1., 1., 1., 1.), 0.), vec3(-.5,1.,1.), vec3(-2.5,-1.,-1.), ray_sphere);*/
//	scene->objects[7] = NULL;

	scene->cam->passes = 0;
//	scene->cam->pos = vec3(0., 0., -5.);
//	scene->cam->orientation = vec4(0., 0., 0., 1.);
//	scene->cam->fov_dist = 1.6;
//	scene->ambient = vec4(0., 0., 0., 0.);

	mlx_hook(scene->window, DestroyNotify, 0, mlx_loop_end, scene->mlx);
	mlx_hook(scene->window, KeyPress, KeyPressMask, on_key_press, &scene);
	mlx_loop_hook(scene->mlx, render, &scene);
	mlx_loop(scene->mlx);
	free_all(scene);
	return 0;
}
