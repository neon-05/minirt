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
	scene->cam->orientation = vec4(tmp->aa, tmpy>ab, tmp->ac, 0); // je mets quoi en dernier argument la ??
	scene->cam->model_view_matrix = NULL; // a faire
	scene->cam->fov_dist = tmp->fov;
}

// scene->obj[i] = object_init(martix, pos, material_init(emmissive, rgba, roughness, refraction_index), border1, border2, ray_func);
void	assign_obj(t_scene *scene, t_val *obj, int i)
{
	t_vec3 pos = vec3(obj->x, obj->y, obj->z);
	t_vec4 rgba = vec4(obj->r, obj->g, obj->b, 1); // je met quoi en a ?
	// matrix ?
	// emmissive ?
	// roughness ?
	// refraction_index ?
	// border1 ?
	// border2 ?
	// ray_func ?
	
	scene->obj[i] = object_init(martix, pos, material_init(emmissive, rgba, roughness, refraction_index), border1, border2, ray_func);
}

void	assign(t_scene *scene, t_parse *parse)
{
	t_val	*tmp;

	tmp = parse->objects;
	assign_cam(scene, parse);
	scene->ambient = colors(&val, val.ratio);
	while (tmp)
	{
		assign_obj(scene, tmp);
		tmp = tmp->next;
	}
}

/*

scene->objects[4] = object_init(i_mat3ig, vec3(3., 0., 0.), material_init(0, vec4(.5, 1., .5, 1.), .5, 1.), vec3(3.,-1.,3.), vec3(3.,5.,-3.), ray_plane);
scene->objects[5] = object_init(i_mat3i, vec3(0., 4., 0.), material_init(1, vec4(1., 1., 1., 1.), 0., 1.), vec3(1.,5.,1.), vec3(-1.,3.,-1.), ray_sphere);

*/
