/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_ispace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:48:25 by malapoug          #+#    #+#             */
/*   Updated: 2025/10/29 11:38:31 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_issispace(char c)
{
	return ((c >= 8 && c <= 13) || c == ' ');
}

int	arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

static int	count_w(const char *s)
{
	int	i;
	int	count;
	int	in_w;

	if (!s)
		return (-1);
	i = 0;
	count = 0;
	in_w = 0;
	while (s[i])
	{
		if (!ft_issispace(s[i]) && in_w == 0)
		{
			count++;
			in_w = 1;
		}
		else if (ft_issispace(s[i]))
			in_w = 0;
		i++;
	}
	return (count);
}

static char	*ft_malloc_w(char *s)
{
	char	*arr;
	int		i;

	i = 0;
	while (s[i] && !ft_issispace(s[i]))
		i++;
	arr = ft_substr(s, 0, i);
	if (!arr)
		return (NULL);
	return (arr);
}

char	**split_ispace(const char *s)
{
	char	**arr;
	int		i;

	i = 0;
	arr = (char **)malloc((count_w(s) + 1) * sizeof(char *));
	if (!arr ||!s)
		return (NULL);
	while (*s)
	{
		while (ft_issispace(*s))
			s++;
		if (*s == '\0')
			break ;
		arr[i] = ft_malloc_w((char *)s);
		if (!arr[i])
		{
			ft_free_arr(arr, i);
			return (NULL);
		}
		i++;
		while (*s && !ft_issispace(*s))
			s++;
	}
	arr[i] = NULL;
	return (arr);
}
