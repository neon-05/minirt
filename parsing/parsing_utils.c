# include "parsing.h"

int	get_line(char **line)
{
	char	*buffer;
	char	c;
	int		bytes;
	int		i;

	i = 0;
	buffer = (char *)malloc(sizeof(char) * 50);
	if (!buffer)
		return (-1);
	bytes = read(0, &c, 1);
	while (bytes && c != '\n')
	{
		if (c != '\n')
			buffer[i] = c;
		i++;
		bytes = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	return (bytes);
}
