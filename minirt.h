#ifndef MINIRT_H
# define MINIRT_H

//====================(INCLUDES)============================//

# include <matft.h>
# include <libft.h>
# include <mlx.h>
# include <mlx_int.h>

//====================(DEFINES)=============================//

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define WIN_TITLE "minirt"
# define RAY_DEPTH_LIMIT 1
# define RAY_PER_BOUNCE 1

//====================(STRUCTS)=============================//

typedef struct s_cam		t_cam;
typedef struct s_scene		t_scene;
typedef struct s_ray		t_ray;
typedef struct s_material	t_material;
typedef struct s_hit_info	t_hit_info;
typedef struct s_object		t_object;

typedef struct s_cam
{
	t_vec3	pos;
	t_vec4	orientation;
	t_mat3	model_view_matrix;
	double	fov_dist;
}	t_cam;

typedef struct s_scene
{
	t_object	**objects;
	t_cam		*cam;
	t_vec4		ambient;
	t_xvar		*mlx;
	t_win_list	*window;
}	t_scene;

typedef struct s_ray
{
	t_vec3	n_director;
	t_vec3	origin;
	double	strength;
}	t_ray;

typedef struct s_material
{
	int			emmissive;
	t_vec4		color;
	double		roughness;
	double		refraction_index;
}	t_material;

typedef struct s_hit_info
{
	double		distance;
	t_object	*object;
}	t_hit_info;

typedef struct s_object
{
	t_mat3		trans_matrix;
	t_vec3		offset;
	t_material	material;
	double		(*ray_dist_func)(t_ray);
}	t_object;

//====================(DECLARATIONS)========================//

// fsh.c
t_vec4 vertex_shader(t_scene *scene, t_vec2 uv);

// initialize_structs.c
t_object	*object_init(
		t_mat3 trans_matrix, t_vec3 offset,
		t_material material, double (*ray_dist_func)(t_ray)
	);
t_material	material_init(int emmissive, t_vec4 color,
		double roughness, double refraction_index
	);

#endif