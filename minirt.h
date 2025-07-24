#ifndef MINIRT_H
# define MINIRT_H

//====================(INCLUDES)============================//

# include <matft.h>
# include <libft.h>
# include <mlx.h>
# include <mlx_int.h>

//====================(DEFINES)=============================//

# define PI 3.14159265358979323846

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define WIN_TITLE "minirt"
# define RAY_DEPTH_LIMIT 1
# define RAY_PER_BOUNCE 1

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_DW 65364
# define KEY_LE 65361
# define KEY_RI 65363
# define KEY_ESC 65307
# define KEY_SH 65505

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
	int		shift_pressed;
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
	double		specularity;
}	t_material;

typedef struct s_hit_info
{
	double		distance;
	t_vec3		normal;
	t_object	*object;
}	t_hit_info;

typedef struct s_object
{
	t_mat3		trans_matrix;
	t_vec3		offset;
	t_material	material;
	t_hit_info	(*ray_func)(t_ray);
}	t_object;

//====================(DECLARATIONS)========================//

// fsh.c
t_vec4 vertex_shader(t_scene *scene, t_vec2 uv);

// initialize_structs.c
t_object	*object_init(
		t_mat3 trans_matrix, t_vec3 offset,
		t_material material, t_hit_info (*ray_func)(t_ray)
	);
t_material	material_init(int emmissive, t_vec4 color,
		double roughness, double refraction_index
	);

double	clamp(double x);
t_vec3 q_rot(t_vec3 v, t_vec4 q);

#endif