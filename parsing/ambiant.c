#include "parsing.h"

static int	get_data(t_val *val, char *line)
{
	val->ratio = atod(val->tab[1]);
	if (!(val->ratio >= 0 && val->ratio <= 1))
		return (printf("%sAmbiant light ratio is not in the range [0.0 - 1.0]\
 (line skipped):\n%s\n\n", val->error, line), SKIPPED);
	val->colors = ft_split(val->tab[2], ',');
	if (!val->colors)
		return (MALLOC_ERROR);
	if (arr_size(val->colors) != 3)
		return (printf("%sAmbiant light has wrong number\
 of arguments for color (line skipped):\n%s\n\n", val->error, line), SKIPPED);
	val->r = ft_atoi(val->colors[0]);
	val->g = ft_atoi(val->colors[1]);
	val->b = ft_atoi(val->colors[2]);
	if (val->r < 0 || val->r > 255 || val->g < 0 \
		|| val->g > 255 || val->b < 0 || val->b > 255)
		return (printf("%sAmbiant light color is not in the range [0 - 255]\
 (line skipped):\n%s\n\n", val->error, line), SKIPPED);
	return (SUCCESS);
}

int	ambiant(t_scene *scene, char **tab, char *line)
{
	t_val	val;

	val.error = RED"ERROR: "RESET;
	val.tab = tab;
	if (get_data(&val, line) == SKIPPED)
		return (SKIPPED);
	scene->ambient = colors(&val, val.ratio);
	return (SUCCESS);
}
