#ifndef MINIRT_H
# define MINIRT_H

# include <matft.h>

enum e_shape_type
{
	POINT = 0,
	PLANE = 1,
	SPHERE = 2,
	CYLINDER = 3
};

typedef struct s_cam
{
	t_vec3	pos;
	t_vec4	orientation;
	t_mat3	model_view_matrix;
	double	fov_dist;
}	t_cam;

typedef struct s_scene
{
	t_object	*objects;
	t_cam		*cam;
	t_vec4		ambient;
}	t_scene;

typedef struct s_ray
{
	t_vec3	n_director;
	t_vec3	origin;
	int		*pixel;
	double	strength;
}	t_ray;

typedef struct s_material
{
	int			emmissive;
	t_vec4		color;
	double		roughness;
	double		refraction_index;
}	t_material;

typedef struct s_object
{
	int			type;
	t_mat3		trans_matrix;
	t_vec3		offset;
	t_material	material;
	double		ray_dist(t_ray, t_object *, t_scene *);
}	t_object;

#endif