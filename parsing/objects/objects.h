/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:39:16 by malapoug          #+#    #+#             */
/*   Updated: 2025/06/25 13:49:41 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

//====================(INCLUDES)============================//

# include "../parsing.h"
# include "../colors.h"

//====================(DEFINES)=============================//

# define SET "ACL"
# define SUCCESS 1
# define MALLOC_ERROR 0
# define SKIPPED 2
# define OPEN_ERROR -1

//====================(STRUCTS)=============================//

typedef struct s_parse
{
	int			n_objects;
	char		*once;
	t_scene		*scene;
}	t_parse;

typedef struct s_val
{
	char		**tab;
	char		*error;

	double		ratio;
	char		**colors;
	double		r;
	double		g;
	double		b;

	char		**xyz;
	char		**orient;
	double		teta;
	double		x;
	double		y;
	double		z;
	double		aa;
	double		ab;
	double		ac;
	double		fov;

	double		diametre;

	double		height;
}	t_val;

//====================(DECLARATIONS)========================//

//ambiant
int		ambiant(t_scene *scene, char **tab, char *line);

//light
int		light(t_scene *scene, char **tab, char *line);

//camera
int		camera(t_scene *scene, char **tab, char *line);

//sphere
int		sphere(t_scene *scene, char **tab, char *line);

//plane
int		plane(t_scene *scene, char **tab, char *line);

//cylinder
int		cylinder(t_scene *scene, char **tab, char *line);

#endif

