/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:39:16 by malapoug          #+#    #+#             */
/*   Updated: 2025/10/20 19:34:43 by malapoug         ###   ########.fr       */
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
typedef struct s_cam		t_cam;
typedef struct s_scene		t_scene;
typedef struct s_ray		t_ray;
typedef struct s_material	t_material;
typedef struct s_hit_info	t_hit_info;
typedef struct s_object		t_object;
typedef struct s_bound_vol	t_bound_vol;

typedef struct s_parse	t_parse;
typedef struct s_val	t_val;

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

//added
int	added(t_parse *parse, char **tab, char *line);

#endif
