#include "parsing.h"

static int	check_data(char **xyz, char **orientation, double fov, char *line)
{
	char	*error;
	// int		x;
	// int		y;
	// int		z;
	(void)xyz;
	// double		x_o;
	// double		y_o;
	// double		z_o;

	error = RED"ERROR: "RESET;
	if (arr_size(orientation) != 3)
		return (printf("%sCamera orientation has wrong number\
 of arguments (line skipped):\n%s\n\n", error, line), SKIPPED);
	// x = ft_atoi(xyz[0]);
	// y = ft_atoi(xyz[1]);
	// z = ft_atoi(xyz[2]);
	if (!(fov >= 0 && fov <= 180))
		return (printf("%sCamera fov is not in the range [0 - 180]\
 (line skipped):\n%s\n\n", error, line), SKIPPED);
	if (arr_size(orientation) != 3)
		return (printf("%sCamera orientaion has wrong number\
 of arguments (line skipped):\n%s\n\n", error, line), SKIPPED);
	// x_o = ft_atod(orientation[0]);
	// y_o = ft_atod(orientation[1]);
	// z_o = ft_atod(orientation[2]);
	// if (x_o < -1 || x_o > 1 || y_o < -1 || y_o > 1 || z_o < -1 || z_o > 1)
		// return (printf("%sCamera orientaion is not in the range [-1 - 1] (line skipped):\n%s\n\n", error, line), SKIPPED);
	return (SUCCESS);
}

int	 camera(t_scene *scene, char **tab, char *line)
{
	char	**xyz;
	char	**orientation;
	int		fov;

	xyz = ft_split(tab[1], ',');
	if (!xyz)
		return (MALLOC_ERROR);
	orientation = ft_split(tab[2], ',');
	if (!xyz)
		return (MALLOC_ERROR);
	fov = atoi(tab[3]);
	if (check_data(xyz, orientation, fov, line) == SKIPPED)
		return (SKIPPED);
	(void)scene;
	return (SUCCESS);
}
