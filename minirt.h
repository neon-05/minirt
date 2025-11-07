/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 15:28:32 by neon-05           #+#    #+#             */
/*   Updated: 2025/11/07 15:49:49 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

//====================(INCLUDES)============================//

# include <matft.h>
# include <libft.h>
# include <mlx.h>
# include <mlx_int.h>
# include <stdlib.h>
# include "parsing/parsing.h"

//====================(DEFINES)=============================//

# define PI 3.141592653589793

# define WIN_WIDTH 1080
# define WIN_HEIGHT 720
# define WIN_TITLE "miniRT"
# define RAY_DEPTH_LIMIT 4
# define RAY_PER_BOUNCE 2
# define MAX_RENDER_PASSES 10

# define LOADING_BAR_LENGTH 100
# define PROGRESS_BAR_SCALE "%:\t-------10v-------20v-------30v-------40v-------50v\
-------60v-------70v-------80v-------90v------100v"

# define LCG_MULT 1103515245
# define LCG_INCR 12345

# define LIGHT_STRENGTH 10.

# define KEY_ESC 65307

//====================(STRUCTS)=============================//

typedef struct s_cam		t_cam;
typedef struct s_scene		t_scene;
typedef struct s_ray		t_ray;
typedef struct s_material	t_material;
typedef struct s_hit_info	t_hit_info;
typedef struct s_object		t_object;
typedef struct s_bound_vol	t_bound_vol;

typedef struct s_cam
{
	t_vec3	pos;
	t_vec4	orientation;
	t_mat3	model_view_matrix;
	t_img	*img;
	t_vec4	*prev_frame;
	double	fov_dist;
	int		passes;
}	t_cam;

typedef struct s_scene
{
	t_object	**objects;
	t_cam		*cam;
	t_vec4		ambient;
	t_xvar		*mlx;
	t_win_list	*window;
	int			lcg_seed;
}	t_scene;

typedef struct s_ray
{
	t_vec3	n_director;
	t_vec3	origin;
}	t_ray;

typedef struct s_material
{
	int			emmissive;
	t_vec4		color;
	double		roughness;
}	t_material;

typedef struct s_hit_info
{
	double		distance;
	t_vec3		point;
	t_vec3		normal;
	t_object	*object;
}	t_hit_info;

typedef struct s_bound_vol
{
	t_vec3	corner1;
	t_vec3	corner2;
}	t_bound_vol;

typedef struct s_object
{
	t_bound_vol	bounding_volume;
	t_mat3		trans_matrix;
	t_mat3		_inv_trans_matrix;
	t_vec3		offset;
	t_material	material;
	t_hit_info	(*ray_func)(t_ray);
}	t_object;

//====================(DECLARATIONS)========================//

// fsh_ray_logic.c
void		fragment_shader(t_scene *scene, t_vec4 *frag_color, t_vec2 uv);

// fsh_math.c
t_vec3		vec3_random_normalized(int *seed);
double		unsigned_max(double a, double b);
double		unsigned_min(double a, double b);
double		clamp(double x);

// initialize_structs.c
t_object	*object_init(t_object o);
t_material	material_init(int emmissive, t_vec4 color,
				double roughness);

double		clamp(double x);
t_vec3		q_rot(t_vec3 v, t_vec4 q);

void		free_obj_arr(t_object **arr);
void		free_all(t_scene *scene);
int			alloc_all(t_scene **scene, const char *filename);

// ray_dist_functions.c
t_hit_info	ray_plane(t_ray ray);
t_hit_info	ray_plane_circle(t_ray ray);
t_hit_info	ray_sphere(t_ray ray);
t_hit_info	ray_cylinder_bound(t_ray ray);
t_hit_info	ray_light(t_ray ray);

// math_utils.c
t_vec4		q_mul(t_vec4 a, t_vec4 b);
t_vec3		q_rot(t_vec3 v, t_vec4 q);
double		mat2_det(t_mat2 m);
double		mat3_det(t_mat3 m);
t_mat3		mat3_inverse(t_mat3 m);

// create_objs.c
int			new_obj(
				const char *id, double *params, t_object **objs, int emmissive);

t_object	*new_light(
				double params[7], t_object **objs, int i, int emmissive);

// input_check.c
void		check_input(int cond, const char *msg, int exit_code);
int			ft_endswith(const char *s, const char *ref);

#endif
