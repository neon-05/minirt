/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 20:28:38 by malapoug          #+#    #+#             */
/*   Updated: 2025/10/31 16:06:35 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	free_val(t_val *val)
{
	if (val->xyz)
		free_tab(val->xyz);
	if (val->orient)
		free_tab(val->orient);
	if (val->colors)
		free_tab(val->colors);
	if (val->tab)
		free_tab(val->tab);
	free(val);
}

void	free_parse(t_parse *parse)
{
	t_val	*tmp;

	if (parse->once)
		free(parse->once);
	if (parse->camera)
		free_val(parse->camera);
	if (parse->ambiant)
		free_val(parse->ambiant);
	if (parse->light)
		free_val(parse->light);
	if (parse->objects)
		tmp = parse->objects->next;
	while (parse->objects)
	{
		if (parse->objects)
			free_val(parse->objects);
		parse->objects = tmp;
		if (tmp)
			tmp = parse->objects->next;
	}
}
