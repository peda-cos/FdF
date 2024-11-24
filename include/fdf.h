/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:50:09 by peda-cos          #+#    #+#             */
/*   Updated: 2024/11/24 14:50:16 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <MLX42/MLX42.h>
# include "../lib/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# ifndef MLX_KEY_PLUS
#  define MLX_KEY_PLUS 334
# endif

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct s_map
{
	int		width;
	int		height;
	t_point	**points;
}	t_map;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*window;
	t_map		*map;
	int			shift_x;
	int			shift_y;
	int			scale;
	float		angle;
}	t_data;

t_map	*parse_map(const char *filename);
void	render_map(t_map *map, mlx_t *mlx, mlx_image_t *window);
void	handle_key(mlx_key_data_t keydata, void *param);
void	free_map(t_map *map);
void	setup_hooks(mlx_t *mlx, t_data *data);
void	error_exit(const char *message);
void	*safe_malloc(size_t size);
void	cleanup(t_data *data);
void	free_double_ptr(char **array);
int		count_words(const char *str, char delimiter);
t_point	*parse_line(const char *line, int y);
t_map	*initialize_map(void);
void	set_projection_parameters(t_data *data);
t_point	project_iso(t_point p, float angle, int scale, int shift_x, int shift_y);
void	draw_line(mlx_t *mlx, mlx_image_t *window, t_point p1, t_point p2);

#endif
