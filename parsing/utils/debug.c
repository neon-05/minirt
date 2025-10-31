/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 20:28:39 by malapoug          #+#    #+#             */
/*   Updated: 2025/10/31 16:30:00 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	print_acl(t_parse parse)
{
	if (parse.ambiant)
		printf(YELLOW"A\t%.2f\t%.2f,%.2f,%.2f\n"RESET, parse.ambiant->ratio,
			parse.ambiant->r, parse.ambiant->g, parse.ambiant->b);
	if (parse.camera)
		printf(YELLOW"C\t %.2f,%.2f,%.2f \t %.2f,%.2f,%.2f \t %.2f \n"RESET,
			parse.camera->x, parse.camera->y, parse.camera->z, parse.camera->aa,
			parse.camera->ab, parse.camera->ac, parse.camera->ratio);
	if (parse.light)
		printf(YELLOW"L\t %.2f,%.2f,%.2f \t %.2f \t %.2f,%.2f,%.2f \n"RESET,
			parse.light->x, parse.light->y, parse.light->z, parse.light->ratio,
			parse.light->r, parse.light->g, parse.light->b);
}

void	show_parse(t_parse parse)
{
	t_val	*tmp;

	tmp = parse.objects;
	print_acl(parse);
	while (tmp)
	{
		if (tmp->type && tmp->type[0] == 'C' && tmp->type[1] == 'y')
			printf(YELLOW"cy\t %.2f,%.2f,%.2f \t %.2f,%.2f,%.2f \t %.2f \t\
				%.2f \t %.2f,%.2f,%.2f \n"RESET, tmp->x, tmp->y, tmp->z,
				tmp->aa, tmp->ab, tmp->ac, tmp->diametre,
				tmp->height, tmp->r, tmp->g, tmp->b);
		else if (tmp->type && tmp->type[0] == 'P' && tmp->type[1] == 'l')
			printf(YELLOW"pl\t %.2f,%.2f,%.2f \t %.2f,%.2f,%.2f \t\
				%.2f,%.2f,%.2f \n"RESET, tmp->x, tmp->y, tmp->z,
				tmp->aa, tmp->ab, tmp->ac, tmp->r, tmp->g, tmp->b);
		else if (tmp->type && tmp->type[0] == 'S' && tmp->type[1] == 'p')
			printf(YELLOW"sp\t %.2f,%.2f,%.2f \t %.2f \t %.2f,%.2f,%.2f \n"
				RESET, tmp->x, tmp->y, tmp->z,
				tmp->diametre, tmp->r, tmp->g, tmp->b);
		tmp = tmp->next;
	}
}
