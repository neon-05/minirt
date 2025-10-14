/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:39:16 by malapoug          #+#    #+#             */
/*   Updated: 2025/10/14 15:39:12 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

//====================(INCLUDES)============================//
# include <matft.h>
# include "../parsing.h"
# include "../colors.h"

//====================(DEFINES)=============================//
# define SET "ACL"
# define SUCCESS 1
# define MALLOC_ERROR 0
# define SKIPPED 2
# define OPEN_ERROR -1

//====================(STRUCTS)=============================//
typedef struct s_parse	t_parse;
typedef struct s_val	t_val;

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

//====================(DECLARATIONS)========================//
//ambiant
int		ambiant(t_parse *parse, char **tab, char *line);

//light
int		light(t_parse *parse, char **tab, char *line);

//camera
int		camera(t_parse *parse, char **tab, char *line);

//sphere
int		sphere(t_parse *parse, char **tab, char *line);

//plane
int		plane(t_parse *parse, char **tab, char *line);

//cylinder
int		cylinder(t_parse *parse, char **tab, char *line);

//boundings
t_vec3	bbox_min_cylinder(t_val val);
t_vec3	bbox_max_cylinder(t_val val);
t_vec3	bbox_min_sphere(t_val val);
t_vec3	bbox_max_sphere(t_val val);

#endif
