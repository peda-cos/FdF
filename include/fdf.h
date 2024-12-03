/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 21:58:43 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/02 22:53:23 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

# include <stdio.h>
# include <fcntl.h>

typedef struct s_map {
	int	width;
	int	height;
	int	**matrix;
}	t_map;

typedef struct s_fdf {
	void	*mlx;
	void	*window;
	t_map	*map;
}	t_fdf;

void	draw_map(t_fdf *data);
t_map	*parse_map(const char *file);
void	free_map(t_map *map);

#endif
