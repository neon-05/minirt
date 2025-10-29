/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 20:28:38 by malapoug          #+#    #+#             */
/*   Updated: 2025/10/29 13:36:58 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
typedef struct s_parse
{
	int				n_objects;
	char			*once;
	t_scene			*scene;

	t_val			*camera;
	t_val			*ambiant;
	t_val			*light;

	t_val			*objects;
	unsigned int	last;
}	t_parse;

typedef struct s_val
{
	char			*type;

	char			**tab;
	char			*error;

	double			ratio;
	char			**colors;
	double			r;
	double			g;
	double			b;

	char			**xyz;
	char			**orient;
	double			teta;
	double			x;
	double			y;
	double			z;
	double			aa;
	double			ab;
	double			ac;
	double			fov;

	double			diametre;

	double			height;

	t_val			*next;

}	t_val;
*/

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

void	free_val(t_val *val)
{
	//if (val->tab)
	//	free_tab(val->tab);
	if (val->xyz)
		free_tab(val->xyz);
	if (val->orient)
		free_tab(val->orient);
	if (val->colors)
		free_tab(val->colors);
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
