#include "../minirt.h"

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
	c |= ((int) (color.w * 255.) & 0xFF) << 24;
	c |= ((int) (color.x * 255.) & 0xFF) << 16;
	c |= ((int) (color.y * 255.) & 0xFF) << 8;
	c |= ((int) (color.z * 255.) & 0xFF) << 0;
	/*
	c |= (int) (color.w * 255.) << 24;
	c |= (int) (color.x * 255.) << 16;
	c |= (int) (color.y * 255.) << 8;
	c |= (int) (color.z * 255.) << 0;
	*/
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

	// if ( > MAX_RENDER_PASSES)
	// 	return (0);
	frag_pos = 0;
	printf("\n");
	while (frag_pos < WIN_WIDTH * WIN_HEIGHT)
	{
		uv = vec2(
			(double) (frag_pos % WIN_WIDTH) / WIN_HEIGHT,
			1.-(double) (frag_pos / WIN_WIDTH) / WIN_HEIGHT
		);
		vertex_shader(*scene, &(*scene)->cam->prev_frame[frag_pos], vec2_sub(vec2_scale(uv, 2.), vec2((double) WIN_WIDTH / WIN_HEIGHT, 1.)));
		pixel_put_image(*scene, (*scene)->cam->img, frag_pos * 4, (*scene)->cam->prev_frame[frag_pos]);
		frag_pos++;
		printf("\033[1A\033[2Kpass %d, pixel %li/%i\n", (*scene)->cam->passes, frag_pos, WIN_WIDTH * WIN_HEIGHT);
	}
	(*scene)->cam->passes++;
	mlx_put_image_to_window((*scene)->mlx, (*scene)->window, (*scene)->cam->img, 0, 0);
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

double	mat2_det(t_mat2 m)
{
	return (m.l1.x * m.l2.y - m.l1.y * m.l2.x);
}

double	mat3_det(t_mat3 m)
{
	t_mat2	subm1;
	t_mat2	subm2;
	t_mat2	subm3;

	subm1 = mat2(vec2(m.l2.y, m.l2.z), vec2(m.l3.y, m.l3.z));
	subm2 = mat2(vec2(m.l2.x, m.l2.z), vec2(m.l3.x, m.l3.z));
	subm3 = mat2(vec2(m.l2.x, m.l2.y), vec2(m.l3.x, m.l3.y));
	return (m.l1.x * mat2_det(subm1) - m.l1.y * mat2_det(subm2) + m.l1.z * mat2_det(subm3));
}

t_mat3	mat3_inverse(t_mat3 m)
{
	double	d;
	t_mat3	m2;

	d = mat3_det(m);

	/*
	a = m.l1.x
	b = m.l1.y
	c = m.l1.z
	d = m.l2.x
	e = m.l2.y
	f = m.l2.z
	g = m.l3.x
	h = m.l3.y
	i = m.l3.z
	*/
	m2 = mat3(
		vec3(m.l2.y * m.l3.z - m.l2.z * m.l3.y, m.l1.z * m.l3.y - m.l1.y * m.l3.z, m.l1.y * m.l2.z - m.l1.z * m.l2.y),
		vec3(m.l2.z * m.l3.x - m.l2.x * m.l3.z, m.l1.x * m.l3.z - m.l1.z * m.l3.x, m.l1.z * m.l2.x - m.l1.x * m.l2.z),
		vec3(m.l2.x * m.l3.y - m.l2.y * m.l3.x, m.l1.y * m.l3.x - m.l1.x * m.l3.y, m.l1.x * m.l2.y - m.l1.y * m.l2.x)
	);

	return (mat3_scale(m2, 1./d));
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
	if (key == KEY_SHIFT)
	{
		printf("unshift\n");
		(*scene)->cam->shift_pressed = 0;
	}
	return (0);
}

int	on_key_press(int key, t_scene **scene)
{
	double angle = 0.174532925;
	double step;

	if ((*scene)->cam->shift_pressed)
		step = .1;
	else
		step = 1.;

	printf("key -p[%i]\n", key);
	if (key == KEY_ESC)
		mlx_loop_end((*scene)->mlx);
	else if (key == KEY_SHIFT)
	{
		printf("shift\n");
		(*scene)->cam->shift_pressed = 1;
	}
	else if (key == KEY_W)
		move_cam(vec3(0., 0., step), (*scene)->cam);
	else if (key == KEY_S)
		move_cam(vec3(0., 0., -step), (*scene)->cam);
	else if (key == KEY_A)
		move_cam(vec3(-step, 0., 0.), (*scene)->cam);
	else if (key == KEY_D)
		move_cam(vec3(step, 0., 0.), (*scene)->cam);
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

void	calculate_inverses(t_object **objs)
{
	size_t	i;

	i = 0;
	while(objs[i])
	{
		objs[i]->_inv_trans_matrix = mat3_inverse(objs[i]->trans_matrix);
		i++;
	}
}

int	main(void)
{
	t_mat3	i_mat3i = mat3(
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
		);

	t_scene	*scene;

	if (alloc_all(&scene, 8))
		return (1);

	scene->objects[0] = object_init(mat3_scale(i_mat3i, 30.), vec3(10., 40., -20.), material_init(1, vec4(1., 1., 1., 1.), 1.), vec3(100.,100.,100.), vec3(-100.,-100.,-100.), ray_sphere);
	scene->objects[1] = object_init(i_mat3i, vec3(0., -1., 0.), material_init(0, vec4(.5, .5, 1., 1.), 1.), vec3(3.,-1.,3.), vec3(-3.,-1.,-3.), ray_plane);
	scene->objects[2] = object_init(i_mat3i2, vec3(0., 0., 3.), material_init(0, vec4(1., 1., 1., 1.), .5), vec3(3.,-1.,3.), vec3(-3.,5.,3.), ray_plane);
	scene->objects[3] = object_init(i_mat3ir, vec3(-3., 0., 0.), material_init(0, vec4(1., .5, .5, 1.), .5), vec3(-3.,-1.,3.), vec3(-3.,5.,-3.), ray_plane);
	scene->objects[4] = object_init(i_mat3ig, vec3(3., 0., 0.), material_init(0, vec4(.5, 1., .5, 1.), .5), vec3(3.,-1.,3.), vec3(3.,5.,-3.), ray_plane);
	scene->objects[5] = object_init(i_mat3i, vec3(0., 4., 2.), material_init(1, vec4(1., 1., 1., 1.), 0.), vec3(1.,5.,1.), vec3(-1.,3.,3.), ray_sphere);
	scene->objects[6] = object_init(i_mat3i, vec3(-1.5, 0., 0.), material_init(0, vec4(1., 1., 1., 1.), 0.), vec3(-.5,1.,1.), vec3(-2.5,-1.,-1.), ray_sphere);
	scene->objects[7] = NULL;

	scene->cam->passes = 0;
	scene->cam->pos = vec3(0., 1.5, -5.);
	scene->cam->orientation = vec4(0., 0., 0., 1.);
	scene->cam->fov_dist = 1.6;
	scene->ambient = vec4(0., 0., 0., 0.);

	calculate_inverses(scene->objects);
	mlx_hook(scene->window, DestroyNotify, 0, mlx_loop_end, scene->mlx);
	mlx_hook(scene->window, KeyPress, KeyPressMask, on_key_press, &scene);
	mlx_hook(scene->window, KeyRelease, KeyReleaseMask, on_key_rel, &scene);
	mlx_loop_hook(scene->mlx, render, &scene);
	mlx_loop(scene->mlx);
	free_all(scene);
	return 0;
}
