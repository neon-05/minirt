#include "parsing.h"

/*




Ambient lighting:
A	0.2		255,255,255
∗ identifier: A
∗ ambient lighting ratio in the range [0.0,1.0]: 0.2
∗ R, G, B colors in the range [0-255]: 255, 255, 255



Camera:
C	-50.0,0,20		0,0,1		70
∗ identifier: C
∗ x, y, z coordinates of the viewpoint: -50.0,0,20
∗ 3D normalized orientation vector, in the range [-1,1] for each x, y, z axis:
0.0,0.0,1.0
∗ FOV: Horizontal field of view in degrees in the range [0,180]: 70




Light:
L	-40.0,50.0,0.0		0.6		10,0,255
∗ identifier: L
∗ x, y, z coordinates of the light point: -40.0,50.0,0.0
∗ the light brightness ratio in the range [0.0,1.0]: 0.6
∗ (unused in mandatory part) R, G, B colors in the range [0-255]: 10, 0, 255



*/

static int	check_a(t_parse *parse, char **tab, char *line)
{
	(void)parse;
	(void)tab;
	(void)line;
	return (SUCCESS);
}

static int	check_l(t_parse *parse, char **tab, char *line)
{
	(void)parse;
	(void)tab;
	(void)line;
	return (SUCCESS);
}

static int	check_c(t_parse *parse, char **tab, char *line)
{
	(void)parse;
	(void)tab;
	(void)line;
	return (SUCCESS);
}

static int	check_numbers(t_parse *parse, char **tab, char *line)
{
	if (tab[0][0] == 'A' && check_a(parse, tab, line) == SKIPPED)
		return (SKIPPED);
	else if (tab[0][0] == 'L' && check_l(parse, tab, line) == SKIPPED)
		return (SKIPPED);
	if (tab[0][0] == 'C' && check_c(parse, tab, line) == SKIPPED)
		return (SKIPPED);
	return (SUCCESS);
}

int	check_line(t_parse *parse, char **tab, char *line)
{
	char	*error;

	error = RED"ERROR: "RESET;
	if (ft_strchr(parse->once, tab[0][0]))
		return (printf("%sUnothorized duplicated object (line skipped):\n%s\n\n", error, line), SKIPPED);
	if (tab[0][0] == 'A' && arr_size(tab) != 3)
		return (printf("%sAmbiant light has wrong number of arguments (line skipped):\n%s\n\n", error, line), SKIPPED);
	else if (tab[0][0] == 'C' && arr_size(tab) != 4)
		return (printf("%sCamera has wrong number of arguments (line skipped):\n%s\n\n", error, line), SKIPPED);
	else if (tab[0][0] == 'L' && arr_size(tab) != 4)
		return (printf("%sLight has wrong number of arguments (line skipped):\n%s\n\n", error, line), SKIPPED);
	else if (check_others(parse, tab, line) == SKIPPED)
		return (SKIPPED);
	if (check_numbers(parse, tab, line) == SKIPPED)
		return (SKIPPED);
	return (SUCCESS);
}

