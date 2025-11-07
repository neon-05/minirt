/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:39:16 by malapoug          #+#    #+#             */
/*   Updated: 2025/11/05 16:06:47 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

//====================(INCLUDES)============================//
# include "../parsing.h"

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

typedef struct s_parse		t_parse;
typedef struct s_val		t_val;

//====================(DECLARATIONS)========================//
//parsing_utils
int		get_line(char **line, int fd);
char	*ft_strjoin_f(char *s1, char *s2);
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
int		arr_size(char **arr);

//init
void	init_parse(t_parse *parse);
void	init_val(t_val *v);

//clear
void	free_parse(t_parse *parse);

//debug
void	show_parse(t_parse parse);

#endif
