/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:39:16 by malapoug          #+#    #+#             */
/*   Updated: 2025/11/05 16:06:43 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

//====================(INCLUDES)============================//
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <libft.h>
# include <matft.h>
# include "colors.h"
//# include <mlx.h>
//# include <mlx_int.h>
# include "../minirt.h"
# include "objects/objects.h"
# include "utils/utils.h"

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

//============(PARSER)================//
//parser
void	init_parse(t_parse *parse);
size_t	parse(t_scene *scene, int fd);

//assign
int		assign(t_scene *scene, t_parse *parse);

//============(OBJCTS)================//
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

//============(UTILS )================//
//parsing_utils
int		get_line(char **line, int fd);
char	*ft_strjoin_f(char *s1, char *s2);
int		arr_size(char **arr);
void	ft_free_arr(char **arr, int i);
double	atod(const char *s);

//check_once
int		check_line(t_parse *parse, char **tab, char *line);
int		is_number(char *str);

//check_others
int		check_others(t_parse *parse, char **tab, char *line);

//tranfs
t_vec4	colors(t_val *val, double a);
t_vec4	quaternion(t_vec3 start, t_vec3 target);

//split_assign
void	free_tab(char **tab);
void	free_val(t_val *val);
int		split_assign_vector(t_val *val, char *object, int i, char *line);
int		split_assign_colors(t_val *val, char *object, int i, char *line);
int		split_assign_position(t_val *val, char *object, int i, char *line);

//split_ispace
char	**split_ispace(const char *s);
int		ft_issispace(char c);

//clear
void	free_parse(t_parse *parse);

//debug
void	show_parse(t_parse parse);

#endif
