#include "parsing.h"

/*
typedef struct s_val
{
	char		**tab;
	char		**clors;
	char		**xyz;
	double		x;
	double		y;
	double		z;
	double		r;
	double		g;
	double		b;
	double		a;
	double		b;
	double		c;
	t_vec3		vect_normal;
	t_vec4		val->orient;
	t_vec4		color;
	double		ratio;
	int			fov;
	double		diametre;
	double		height;
}	t_val;
*/

static int	get_data(t_val *val, t_scene *scene, char *line)
{
	if (arr_size(val->orient) != 3)
		return (printf("%sCamera val->orient has wrong number\
 of arguments (line skipped):\n%s\n\n", val->error, line), SKIPPED);
	val->xyz = ft_split(val->tab[1], ',');
	if (!val->xyz)
		return (MALLOC_ERROR);
	val->x = ft_atoi(val->xyz[0]);
	val->y = ft_atoi(val->xyz[1]);
	val->z = ft_atoi(val->xyz[2]);
	scene->cam->pos = vec3(val->x, val->y, val->z);
	val->orient = ft_split(val->tab[2], ',');
	if (!val->orient)
		return (MALLOC_ERROR);
	if (arr_size(val->orient) != 3)
		return (printf("%sCamera orientaion has wrong number\
 of arguments (line skipped):\n%s\n\n", val->error, line), SKIPPED);
	val->aa = atod(val->orient[0]);
	val->ab = atod(val->orient[1]);
	val->ac = atod(val->orient[2]);
	if (val->aa < -1 || val->aa > 1 || val->ab < -1 || val->ab > 1 || val->ac < -1 || val->ac > 1)
		return (printf("%sCamera orientaion is not in the range [-1 - 1]\
 (line skipped):\n%s\n\n", val->error, line), SKIPPED);
	scene->cam->orientation = quaternion(val->aa, val->ab, val->ac, 0);
	return (SUCCESS);
}

int	camera(t_scene *scene, char **tab, char *line)
{
	t_val	val;

	val.error = RED"ERROR: "RESET;
	val.tab = tab;
	if (get_data(&val, scene, line) == SKIPPED)
		return (SKIPPED);
	scene->cam->fov_dist = atod(tab[3]);
	if (!(scene->cam->fov_dist >= 0 && scene->cam->fov_dist <= 180))
		return (printf("%sCamera fov is not in the range [0 - 180]\
 (line skipped):\n%s\n\n", val.error, line), SKIPPED);
	scene->cam->fov_dist = cos(scene->cam->fov_dist / 2.);
	return (SUCCESS);
}
