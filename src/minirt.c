#include "../minirt.h"

t_hit_info	ray_plane(t_ray ray)
{
	t_hit_info	ret;

	ret.normal = vec3(0., 1., 0.);
	if (ray.n_director.y != 0.)
		ret.distance = -(ray.origin.y) / ray.n_director.y;
	else
		ret.distance = -1.;
	return (ret);
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
	ret.normal = vec3_add(ray.origin, vec3_scale(ray.n_director, ret.distance));
	return (ret);
}

double	clamp(double x)
{
	if (x > 1.)
		return (1.);
	else if (0. > x)
		return (0.);
	else
		return (x);
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

int	render(t_scene **scene)
{
	size_t	frag_pos;
	t_vec4	frag_color;
	t_vec2	uv;
	t_img	*img;

	img = mlx_new_image((*scene)->mlx, WIN_WIDTH, WIN_HEIGHT);
	frag_pos = 0;
	while (frag_pos < WIN_WIDTH * WIN_HEIGHT)
	{
		uv = vec2(
			(double) (frag_pos % WIN_WIDTH) / WIN_HEIGHT,
			1.-(double) (frag_pos / WIN_WIDTH) / WIN_HEIGHT
		);
		frag_color = vertex_shader(*scene, vec2_sub(vec2_scale(uv, 2.), vec2((double) WIN_WIDTH / WIN_HEIGHT, 1.)));
		pixel_put_image(*scene, img, frag_pos * 4, vec4_func(frag_color, clamp));
		frag_pos++;
	}
	mlx_put_image_to_window((*scene)->mlx, (*scene)->window, img, 0, 0);
	mlx_destroy_image((*scene)->mlx, img);
	return (0);
}

t_vec4 q_mul(t_vec4 a, t_vec4 b)
{
	return(vec4(
		(a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y),
		(a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x),
		(a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w),
		(a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z)
	));
}

t_vec3 q_rot(t_vec3 v, t_vec4 q)
{
	return vec3_add(v, vec3_scale(vec3_cross( vec3(q.x, q.y, q.z), vec3_add(vec3_cross( vec3(q.x, q.y, q.z), v ), vec3_scale(v, q.w))), 2.));
}

void	move_cam(t_vec3 v, t_cam *cam)
{
	printf("cam[%p](%f, %f, %f)\n", cam, cam->pos.x, cam->pos.y, cam->pos.z);
	cam->pos = vec3_add(cam->pos, q_rot(v, cam->orientation));
}

void	rot_cam(t_vec4 q, t_cam *cam)
{
	printf("rcam[%p](%f, %f, %f, %f)\n", cam, cam->orientation.x, cam->orientation.y, cam->orientation.z, cam->orientation.w);
	cam->orientation = q_mul(cam->orientation, q);
}

int	on_key_rel(int key, t_scene **scene)
{
	printf("key -r[%i]\n", key);
	if (key == KEY_SH)
	{
		printf("unshift\n");
		(*scene)->cam->shift_pressed = 0;
	}
	return (0);
}

int	on_key_press(int key, t_scene **scene)
{
	double angle = 0.174532925;

	printf("key -p[%i]\n", key);
	if (key == KEY_ESC)
		mlx_loop_end((*scene)->mlx);
	else if (key == KEY_SH)
	{
		printf("shift\n");
		(*scene)->cam->shift_pressed = 1;
	}
	else if (key == KEY_W)
		move_cam(vec3(0., 0., 1.), (*scene)->cam);
	else if (key == KEY_S)
		move_cam(vec3(0., 0., -1.), (*scene)->cam);
	else if (key == KEY_A)
		move_cam(vec3(-1., 0., 0.), (*scene)->cam);
	else if (key == KEY_D)
		move_cam(vec3(1., 0., 0.), (*scene)->cam);
	else if (key == KEY_RI)
	{
		if ((*scene)->cam->shift_pressed)
			rot_cam(vec3to4(vec3_scale(vec3(0.,0.,1.), sin(-angle/2.)), cos(-angle/2.)), (*scene)->cam);
		else
			rot_cam(vec3to4(vec3_scale(vec3(0.,1.,0.), sin(angle/2.)), cos(angle/2.)), (*scene)->cam);
	}
	else if (key == KEY_LE)
	{
		if ((*scene)->cam->shift_pressed)
			rot_cam(vec3to4(vec3_scale(vec3(0.,0.,1.), sin(angle/2.)), cos(angle/2.)), (*scene)->cam);
		else
			rot_cam(vec3to4(vec3_scale(vec3(0.,1.,0.), sin(-angle/2.)), cos(-angle/2.)), (*scene)->cam);
	}
	else if (key == KEY_DW)
		rot_cam(vec3to4(vec3_scale(vec3(1.,0.,0.), sin(angle/2.)), cos(angle/2.)), (*scene)->cam);
	else if (key == KEY_UP)
		rot_cam(vec3to4(vec3_scale(vec3(1.,0.,0.), sin(-angle/2.)), cos(-angle/2.)), (*scene)->cam);
	return (0);
}

int	main(void)
{
	t_mat3	i_mat3i = mat3(
			vec3(1., 0., 0.),
			vec3(0., 1., 0.),
			vec3(0., 0., 1.)
		);
	t_mat3	i_mat3 = mat3(
			vec3(1., 0., 0.),
			vec3(0., 2., 0.),
			vec3(0., 0., 1.)
		);

	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	scene->cam = malloc(sizeof(t_cam));
	scene->objects = malloc(sizeof(t_object *) * 4);

	scene->objects[0] = object_init(i_mat3, vec3(0., 0., 3.), material_init(0, vec4(1., 1., 0., 1.), 1., 1.), ray_sphere);
	scene->objects[1] = object_init(i_mat3i, vec3(2.5, -.75, 1.), material_init(1, vec4(1., 1., 1., 1.), 1., 1.), ray_sphere);
	scene->objects[2] = object_init(i_mat3i, vec3(0., -1., 0.), material_init(0, vec4(1., 0., 1., 1.), 1., 1.), ray_plane);
	scene->objects[3] = NULL;

	scene->cam->pos = vec3(0., 0., -10.);
	scene->cam->orientation = vec4(0., 0., 0., 1.);
	scene->cam->fov_dist = 1.6;
	scene->ambient = vec4(0., 0.8, 1., 1.);
	printf("cam(%p)\n", scene->cam);

	scene->mlx = mlx_init();
	scene->window = mlx_new_window(scene->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);

	mlx_hook(scene->window, DestroyNotify, 0, mlx_loop_end, scene->mlx);
	mlx_hook(scene->window, KeyPress, KeyPressMask, on_key_press, &scene);
	mlx_hook(scene->window, KeyRelease, KeyReleaseMask, on_key_rel, &scene);
	mlx_loop_hook(scene->mlx, render, &scene);
	mlx_loop(scene->mlx);
	mlx_destroy_window(scene->mlx, scene->window);
	mlx_destroy_display(scene->mlx);

	free(scene->cam);
	free(scene->objects);
	free(scene);
	return 0;
}
