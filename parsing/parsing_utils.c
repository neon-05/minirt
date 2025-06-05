# include "parsing.h"

int	get_line(char **line, int fd)
{
	char	*buffer;
	char	c;
	int		bytes;
	int		i;

	i = 0;
	buffer = (char *)malloc(sizeof(char) * 50);
	if (!buffer)
		return (-1);
	bytes = read(fd, &c, 1);
	while (bytes && c != '\n')
	{
		if (c != '\n')
			buffer[i] = c;
		i++;
		bytes = read(fd, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	return (bytes);
}

char	*ft_strjoin_f(char *s1, char *s2)
{
	char	*ptr;
	int		size;
	int		i;
	int		j;

	if (!s1)
		return (ft_strdup(s2));
	i = 0;
	size = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	ptr = (char *)malloc(size * sizeof(char));
	if (!ptr)
		return (0);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	free(s1);
	return (ptr);
}

int	arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	ft_free_arr(char **arr, int i)
{
	while (i > 0)
		free(arr[i--]);
	free(arr[i]);
	if (arr)
		free(arr);
}

double	atod(const char *s)
{
	double	n;
	double	frac;
	double	power;
	int		sign;
	size_t	i;

	n = 0;
	frac = 0;
	sign = 1;
	i = 0;
	if (!s)
		return (0);
	n = ft_atoi(s);
	if (s[i] == '.')
	{
		i++;
		power = 0.1;
		while (ft_isdigit(s[i]))
		{
			frac += (s[i] - '0') * power;
			power *= 0.1;
			i++;
		}
	}
	return (sign * (n + frac));
}
