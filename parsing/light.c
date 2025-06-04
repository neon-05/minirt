#include "parsing.h"

static int	check_data(char **xyz, double ratio, char **colors, char *line)
{
	char	*error;
	// int		x;
	// int		y;
	// int		z;
	(void)xyz;
	int		r;
	int		g;
	int		b;

	error = RED"ERROR: "RESET;
	// x = ft_atoi(xyz[0]);
	// y = ft_atoi(xyz[1]);
	// z = ft_atoi(xyz[2]);
	if (!(ratio >= 0 && ratio <= 1))
		return (printf("%sAmbiant light ratio is not in the range [0.0 - 1.0]\
 (line skipped):\n%s\n\n", error, line), SKIPPED);
	if (arr_size(colors) != 3)
		return (printf("%sAmbiant light has wrong number\
 of arguments for color (line skipped):\n%s\n\n", error, line), SKIPPED);
	r = ft_atoi(colors[0]);
	g = ft_atoi(colors[1]);
	b = ft_atoi(colors[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (printf("%sAmbiant light color is not in the range [0 - 255]\
 (line skipped):\n%s\n\n", error, line), SKIPPED);
	return (SUCCESS);
}

int	 light(t_scene *scene, char **tab, char *line)
{
	char	**xyz;
	char	**colors;
	double	ratio;

	ratio = 0;
	xyz = ft_split(tab[1], ',');
	if (!xyz)
		return (MALLOC_ERROR);
	colors = ft_split(tab[3], ',');
	if (!xyz)
		return (MALLOC_ERROR);
	// ratio = atod(tab[2]);
	if (check_data(xyz, ratio, colors, line) == SKIPPED)
		return (SKIPPED);
	(void)scene;
	return (SUCCESS);
}
