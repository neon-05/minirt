/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:54:48 by malapoug          #+#    #+#             */
/*   Updated: 2025/06/25 15:22:08 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing.h"

/*

typedef struct s_object
{
	t_mat3		trans_matrix;
	t_vec3		offset;
	t_material	material;
	double		(*ray_dist_func)(t_ray);
}	t_object;

typedef struct s_scene
{
	t_object	**objects;
	t_cam		*cam;
	t_vec4		ambient;
	t_xvar		*mlx;
	t_win_list	*window;
}	t_scene;

*/

t_material	material_init(int emmissive, t_vec4 color, double roughness, double refraction_index
	)
{
	t_material	r;

	r.emmissive = emmissive;
	r.color = color;
	r.roughness = roughness;
	r.refraction_index = refraction_index;
	return (r);
}

t_object	*object_init(t_mat3 trans_matrix, t_vec3 offset, t_material material, double (*ray_dist_func)(t_ray))
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (MALLOC_ERROR);
	obj->trans_matrix = trans_matrix;
	obj->offset = offset;
	obj->material = material;
	obj->ray_dist_func = ray_dist_func;
	return (obj);
}

int	once_objects(t_parse *parse, char **tab, char *line)
{
	if (check_line(parse, tab, line) == SKIPPED)
		return (free_tab(tab), SKIPPED);
	parse->once = ft_strjoin_f(parse->once, tab[0]);
	if (!parse->once)
		return (free_tab(tab), MALLOC_ERROR);
	if (tab[0][0] == 'A' && ambiant(parse->scene, tab, line) == SKIPPED)
		return (free_tab(tab), SKIPPED);
	else if (tab[0][0] == 'L' && light(parse->scene, tab, line) == SKIPPED)
		return (free_tab(tab), SKIPPED);
	else if (tab[0][0] == 'C' && camera(parse->scene, tab, line) == SKIPPED)
		return (free_tab(tab), SKIPPED);
	printf(GREEN"%s\n"RESET, line);//print what's accepeted
	return (free_tab(tab), SUCCESS);
}

int	others_objects(t_parse *parse, char **tab, char *line)
{
	if (check_others(parse, tab, line) == SKIPPED)
		return (free_tab(tab), SKIPPED);
	if (tab[0][0] == 's' && tab[0][1] == 'p' && sphere(parse->scene, tab, line) == SKIPPED)
		return (free_tab(tab), SKIPPED);
	else if (tab[0][0] == 'p' && tab[0][1] == 'l' && plane(parse->scene, tab, line) == SKIPPED)
		return (free_tab(tab), SKIPPED);
	else if (tab[0][0] == 'c' && tab[0][1] == 'y' && cylinder(parse->scene, tab, line) == SKIPPED)
		return (free_tab(tab), SKIPPED);
	parse->n_objects++;
	printf(GREEN"%s\n"RESET, line);
	return (free_tab(tab), SUCCESS);
}

int	get_data(t_parse *parse, char *line)
{
	char	**tab;
	char	*error;

	error = RED"ERROR: "RESET;
	tab = split_ispace(line);
	if (!tab)
		return (MALLOC_ERROR);
	if (!(arr_size(tab) >= 3 && arr_size(tab) <= 6))
		return (free_tab(tab), SUCCESS);
	if (ft_strlen(tab[0]) == 1 && ft_strchr("ACL", tab[0][0]))
		return (once_objects(parse, tab, line));
	else if (ft_strlen(tab[0]) == 2 && tab[0][0] == '/' && tab[0][1] == '/')
		return (free_tab(tab), SUCCESS);
	else if (ft_strlen(tab[0]) == 2) // &&...
		return (others_objects(parse, tab, line));
	else
	{
		printf("%sUnrecognized object :\n%s\n\n", error, line);
		free_tab(tab);
		return (SKIPPED);
	}
	return (SUCCESS);
}

void	free_parse(t_parse *parse)
{
	if (parse->once)
		free(parse->once);
	//free_scene(psrae->scene);
}

size_t	parse(t_scene *scene, int fd)//n of line parsed ?
{
	t_parse		parse = {0};
	char		*line;
	int			status;

	parse.scene = scene;
	while (get_line(&line, fd))
	{
		status = get_data(&parse, line);
		free(line);
		if (status == MALLOC_ERROR)
			return (free_parse(&parse), MALLOC_ERROR);
		else if (status == SKIPPED)
			return (free_parse(&parse), SKIPPED);
	}
	if (line)
		free(line);
	return (free_parse(&parse), SUCCESS);
}

int	main(int ac, char **av)
{
	t_scene		*scene;
	int			fd;
	t_mat3		i_mat3i;

	// t_mat3	i_mat3 = mat3(vec3(1., 0., 0.), vec3(0., sqrt(3.)/.2, -.5), vec3(0., .5, sqrt(3.)/.2));
	i_mat3i = mat3(vec3(1., 0., 0.), vec3(0., 1., 0.), vec3(0., 0., 1.));
	scene = malloc(sizeof(t_scene));
	scene->cam = malloc(sizeof(t_cam));
	scene->objects = malloc(sizeof(t_object *) * 4);
	scene->cam->pos = vec3(0., 0., -1.);
	scene->objects[0] = object_init(i_mat3i, vec3(0., 0., 3.), material_init(0, vec4(1., 1., 0., 1.), 1., 1.), NULL); //dist_sphere);
	scene->objects[1] = object_init(i_mat3i, vec3(2.5, -.75, 1.), material_init(0, vec4(1., 1., 1., 1.), 1., 1.), NULL); //dist_sphere);
	scene->objects[2] = object_init(i_mat3i, vec3(0., -1., 0.), material_init(0, vec4(1., 0., 1., 1.), 1., 1.), NULL); //dist_plane);
	scene->objects[3] = NULL;
	fd = open("./config.rt", O_RDONLY);
	if (fd < 0)
		fd = open("parsing/config.rt", O_RDONLY);
	if (fd < 0)
		return (MALLOC_ERROR);
	parse(scene, fd);
	(void)ac;
	(void)av;
}

//if line not valid skipp, add 1 to return value


// R resolution int int



// scene->objects[0] = object_init(mat3_scale(i_mat3i, 1./30.), vec3(10., 40., -20.), material_init(1, vec4(1., 1., 1., 1.), 1., 1.), vec3(100.,100.,100.), vec3(-100.,-100.,-100.), ray_sphere);
										//					 offset				   material_init(emmissive, vec4(RGBA,roughness,refraction_index) , b1, b2,              t_hit_info (*ray_func)(t_ray)
