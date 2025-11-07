/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:39:56 by malapoug          #+#    #+#             */
/*   Updated: 2025/11/07 15:07:10 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	get_line(char **line, int fd)
{
	char	*buffer;
	char	c;
	int		bytes;
	int		i;

	i = 0;
	buffer = (char *)malloc(sizeof(char) * 200);
	if (!buffer)
		return (-1);
	bytes = read(fd, &c, 1);
	if (bytes == 0)
		return (free(buffer), 0);
	while (bytes > 0 && c != '\n')
	{
		buffer[i] = c;
		i++;
		bytes = read(fd, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	return (ft_strlen(buffer));
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

void	ft_free_arr(char **arr, int i)
{
	while (i > 0)
		free(arr[i--]);
	free(arr[i]);
	if (arr)
		free(arr);
}

double	atod2(const char *s, double n, int sign)
{
	double	frac;
	double	power;

	frac = 0;
	power = 0.1;
	if (*s == '.')
	{
		s++;
		while (ft_isdigit(*s))
		{
			frac += (*s - '0') * power;
			power *= 0.1;
			s++;
		}
	}
	return (sign * (n + frac));
}

double	atod(const char *s)
{
	double	n;
	int		sign;

	n = 0;
	sign = 1;
	if (!s)
		return (0);
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	n = ft_atoi(s);
	while (*s && *s != '.')
		s++;
	return (atod2(s, n, sign));
}
