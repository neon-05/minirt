/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:39:56 by malapoug          #+#    #+#             */
/*   Updated: 2025/10/15 18:31:40 by malapoug         ###   ########.fr       */
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

double	atod(const char *s)// a bosseeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeer
{
	double	n;
	double	frac;
	double	power;
	int		sign;

	n = 0;
	frac = 0;
	sign = 1;
	power = 0.1;
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
