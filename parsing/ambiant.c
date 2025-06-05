#include "parsing.h"

static int	check_data(char **colors, double ratio, char *line)
{
	char	*error;
	int		r;
	int		g;
	int		b;

	error = RED"ERROR: "RESET;
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

int	ambiant(t_scene *scene, char **tab, char *line)
{
	char	**colors;
	double	ratio;

	colors = ft_split(tab[2], ',');
	if (!colors)
		return (MALLOC_ERROR);
	ratio = atod(tab[1]);
	if (check_data(colors, ratio, line) == SKIPPED)
		return (SKIPPED);
	(void)scene;
	return (SUCCESS);
}
