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

static int	on_key_press(int key, t_scene **scene)
{
	printf("key -p[%i]\n", key);
	if (key == KEY_ESC)
		mlx_loop_end((*scene)->mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_scene	*scene;
	int		fd;

	if (argc < 2)
		return (ft_putendl_fd("missing filename", 2), 1);
	if (alloc_all(&scene))
		return (2);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0 || parse(scene, fd) != SUCCESS)
	{
		if (fd < 0)
			ft_putendl_fd("could not open file", 2);
		else
			ft_putendl_fd("allocation error", 2);
		free_all(scene);
		return (2);
	}
	mlx_hook(scene->window, DestroyNotify, 0, mlx_loop_end, scene->mlx);
	mlx_hook(scene->window, KeyPress, KeyPressMask, on_key_press, &scene);
	mlx_loop_hook(scene->mlx, render, &scene);
	mlx_loop(scene->mlx);
	free_all(scene);
	return (0);
}
