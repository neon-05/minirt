#ifndef PARSING_H
# define PARSING_H

//====================(INCLUDES)============================//

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <libft.h>
# include <matft.h>
# include "colors.h"
//# include <mlx.h>
//# include <mlx_int.h>
//# include "../minirt.h"

//====================(DEFINES)=============================//

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define WIN_TITLE "minirt"
# define RAY_DEPTH_LIMIT 1
# define RAY_PER_BOUNCE 1

# define SET "ACL"
# define MALLOC_ERROR 0
# define SUCCESS 1
# define SKIPPED 2
# define OPEN_ERROR -1

# define ERROR "RED"ERROR: "RESET"


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
	// t_xvar		*mlx;
	// t_win_list	*window;
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

typedef struct s_parse
{
	int			n_objects;
	char		*once;
	size_t		skipped_lines;
	t_scene 	*scene;
}	t_parse;

typedef struct s_val
{
	char		**tab;
	char		*error;

	double		ratio;
	char		**colors;
	double		r;
	double		g;
	double		b;

	char		**xyz;
	char		**orient;
	double		teta;
	double		x;
	double		y;
	double		z;
	double		aa;
	double		ab;
	double		ac;
	double		fov;

	double		diametre;

	double		height;
}	t_val;

//====================(DECLARATIONS)========================//

//parser
size_t	parse(t_scene *scene, int fd);

//parsing_utils
int		get_line(char **line, int fd);
char	*ft_strjoin_f(char *s1, char *s2);
int		arr_size(char **arr);
void	ft_free_arr(char **arr, int i);
double	atod(const char *s);

//check_lines
int	check_line(t_parse *parse, char **tab, char *line);

//check_others
int	check_others(t_parse *parse, char **tab, char *line);

//ambiant
int	 ambiant(t_scene *scene, char **tab, char *line);

//light
int	 light(t_scene *scene, char **tab, char *line);

//camera
int	 camera(t_scene *scene, char **tab, char *line);

//tranfs
t_vec4	colors(t_val *val, double a);
t_vec4	quaternion(double a, double b, double c, double teta);

#endif
