#include "parsing.h"

static int	check_pl(t_parse *parse, char **tab, char *line)
{
	(void)parse;
	(void)tab;
	(void)line;
	return (SUCCESS);
}

static int	check_sp(t_parse *parse, char **tab, char *line)
{
	(void)parse;
	(void)tab;
	(void)line;
	return (SUCCESS);
}

static int	check_cy(t_parse *parse, char **tab, char *line)
{
	(void)parse;
	(void)tab;
	(void)line;
	return (SUCCESS);
}

static int	check_numbers(t_parse *parse, char **tab, char *line)
{
	if (tab[0][0] == 's' && tab[0][1] == 'p' && check_sp(parse, tab, line) == SKIPPED)
		return (SKIPPED);
	else if (tab[0][0] == 'c' && tab[0][1] == 'y' && check_cy(parse, tab, line) == SKIPPED)
		return (SKIPPED);
	else if (tab[0][0] == 'p' && tab[0][1] == 'l' && check_pl(parse, tab, line) == SKIPPED)
		return (SKIPPED);
	return (SUCCESS);
}

int	check_others(t_parse *parse, char **tab, char *line)
{

	char	*error;

	(void)parse;
	error = RED"ERROR: "RESET;
	if (tab[0][0] == 's' && tab[0][1] == 'p' && arr_size(tab) != 4)
		return (printf("%sSphere light has wrong number of arguments (line skipped):\n%s\n\n", error, line), SKIPPED);
	else if (tab[0][0] == 'p' && tab[0][1] == 'l' && arr_size(tab) != 4)
		return (printf("%sPlane has wrong number of arguments (line skipped):\n%s\n\n", error, line), SKIPPED);
	else if (tab[0][0] == 'c' && tab[0][1] == 'y' && arr_size(tab) != 5)
		return (printf("%sCylinlder has wrong number of arguments (line skipped):\n%s\n\n", error, line), SKIPPED);
	if (check_numbers(parse, tab, line) == SKIPPED)
		return (SKIPPED);
	return (SUCCESS);
}
