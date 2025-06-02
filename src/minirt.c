#include "../minirt.h"

double	dist_plane(t_ray ray, t_object *object)
{
	if (ray.n_director.y < 0.)
		return (-(ray.origin.y) / ray.n_director.y);
	else
		return (-1.);
}

double	dist_sphere(t_ray ray)
{
	double	d1;
	double	d2;
	t_vec3	p2;

	d1 = -vec3_dot(ray.n_director, ray.origin);
	p2 = vec3_add(ray.origin, vec3_scale(ray.n_director, d1));
	d2 = vec3_length(p2);
	if (fabs(d2) > 1.)
		return (-1.);
	else
		return (d1 - sqrt(1. - d2));
}

unsigned int	color_from_vec4(t_vec4 color)
{
	unsigned int	c;

	c = 0;
	c |= (int) (color.w * 255.) << 24;
	c |= (int) (color.x * 255.) << 16;
	c |= (int) (color.y * 255.) << 8;
	c |= (int) (color.z * 255.) << 0;
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

void	render(t_scene *scene)
{
	size_t	frag_pos;
	t_vec4	frag_color;
	t_vec2	uv;
	t_img	*img;

	img = mlx_new_image(scene->mlx, WIN_WIDTH, WIN_HEIGHT);
	frag_pos = 0;
	while (frag_pos < WIN_WIDTH * WIN_HEIGHT)
	{
		uv = vec2(
			(double) (frag_pos % WIN_WIDTH) / WIN_HEIGHT,
			1.-(double) (frag_pos / WIN_WIDTH) / WIN_HEIGHT
		);
		frag_color = vertex_shader(scene, vec2_sub(vec2_scale(uv, 2.), vec2((double) WIN_WIDTH / WIN_HEIGHT, 1.)));
		pixel_put_image(scene, img, frag_pos * 4, frag_color);
		frag_pos++;
	}
	mlx_put_image_to_window(scene->mlx, scene->window, img, 0, 0);
	mlx_destroy_image(scene->mlx, img);
}

int	main(int, char const *[])
{
	t_mat3	i_mat3 = mat3(
			vec3(1., 0., 0.),
			vec3(0., sqrt(3.)/.2, -.5),
			vec3(0., .5, sqrt(3.)/.2)
		);
	
	t_mat3	i_mat3i = mat3(
			vec3(1., 0., 0.),
			vec3(0., 1., 0.),
			vec3(0., 0., 1.)
		);

	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	scene->cam = malloc(sizeof(t_cam));
	scene->objects = malloc(sizeof(t_object *) * 4);

	scene->objects[0] = object_init(i_mat3i, vec3(0., 0., 3.), material_init(0, vec4(1., 1., 0., 1.), 1., 1.), dist_sphere);
	scene->objects[1] = object_init(i_mat3i, vec3(2.5, -.75, 1.), material_init(0, vec4(1., 1., 1., 1.), 1., 1.), dist_sphere);
	scene->objects[2] = object_init(i_mat3i, vec3(0., -1., 0.), material_init(0, vec4(1., 0., 1., 1.), 1., 1.), dist_plane);
	scene->objects[3] = NULL;

	scene->cam->pos = vec3(0., 0., -1.);
	scene->cam->fov_dist = 1.25;
	scene->ambient = vec4(0., 0.8, 1., 1.);

	scene->mlx = mlx_init();
	scene->window = mlx_new_window(scene->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);

	mlx_hook(scene->window, DestroyNotify, 0, mlx_loop_end, scene->mlx);
	render(scene);
	mlx_loop(scene->mlx);
	mlx_destroy_window(scene->mlx, scene->window);
	mlx_destroy_display(scene->mlx);

	return 0;
}
