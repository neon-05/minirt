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
	t_mat3	model_view_matrix;
	double	fov_dist;
}

void	assign(t_scene *scene, t_parse *parse)
{
	assign_cam(scene, parse);
	assign_ambiant(scene, parse);
}
