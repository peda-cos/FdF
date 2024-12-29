/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:02:26 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/28 21:41:44 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <string.h>

# define WIDTH 1200
# define HEIGHT 1000
# define TRANSLATE_STEP 5

# define ERROR_FILE_EXTENSION "ERROR: The file must have a .fdf extension."
# define ERROR_FILE_OPEN "ERROR: Unable to open the specified file."
# define ERROR_MAP_WIDTH "ERROR: All map lines must have the same width."
# define ERROR_MAP_FORMAT "ERROR: The map format is invalid."
# define ERROR_MAP_EMPTY "ERROR: The map file is empty."

typedef struct s_point
{
	int				x;
	int				y;
	int				z;
	uint32_t		color;
}					t_point;

typedef struct s_map
{
	unsigned int	width;
	unsigned int	height;
	unsigned int	total_points;
	int				min_z;
	int				max_z;
	t_point			*points;
}					t_map;

typedef struct s_camera
{
	int				projection_type;
	float			zoom_level;
	double			z_scale_factor;
	int				x_offset;
	int				y_offset;
}					t_camera;

typedef struct s_fdf
{
	t_map			*map;
	t_camera		*camera;
	mlx_t			*mlx_instance;
	mlx_image_t		*image;
}					t_fdf;

typedef struct s_bresenham
{
	int				delta_x;
	int				delta_y;
	int				step_x;
	int				step_y;
	int				error;
	int				initial_x;
	int				initial_y;
}					t_bresenham;

enum				e_projection_types
{
	ISOMETRIC,
};

void				initialize_camera(t_fdf *fdf);
void				reset_camera(t_fdf *fdf);
t_point				project_point(t_point point, t_fdf *fdf);
t_map				*initialize_map(void);
void				free_map(t_map *map);
int					count_columns(char *line, char delimiter);
int					validate_file_extension(char *file);
void				load_map(char *file, t_map *map);
void				fill_map(char *file, t_map *map);
void				parse_line_into_points(char *line, t_map *map,
						int line_index);
int					linear_interpolation(int start, int end, float ratio);
uint32_t			interpolate_color(t_point start, t_point end,
						t_bresenham bresenham_state);
uint32_t			convert_hex_to_rgba(unsigned int hex_value);
uint32_t			parse_color(char *line);
void				initialize_bresenham(t_point start, t_point end,
						t_bresenham *bresenham_state);
int					is_within_pixel_boundaries(t_point *point);
void				clear_image_background(mlx_image_t *image);
void				render_map(t_fdf *fdf);
void				draw_line(t_point start, t_point end, mlx_image_t *image);
void				set_hooks(t_fdf *fdf);
void				handle_exit(void *param);
void				handle_translation(void *param);
void				handle_zoom(void *param);
void				free_string_array(char **array);
void				exit_with_error(char *error_message);

#endif
