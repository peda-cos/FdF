#include "fdf.h"
#include <math.h>

static void	apply_rotation_x(t_point *point, double angle)
{
	long	tmp_y;
	long	tmp_z;

	tmp_y = point->y;
	tmp_z = point->value;
	point->y = tmp_y * cos(angle) - tmp_z * sin(angle);
	point->value = tmp_y * sin(angle) + tmp_z * cos(angle);
}

static void	apply_rotation_y(t_point *point, double angle)
{
	long	tmp_x;
	long	tmp_z;

	tmp_x = point->x;
	tmp_z = point->value;
	point->x = tmp_x * cos(angle) + tmp_z * sin(angle);
	point->value = -tmp_x * sin(angle) + tmp_z * cos(angle);
}

static void	apply_rotation_z(t_point *point, double angle)
{
	long	tmp_x;
	long	tmp_y;

	tmp_x = point->x;
	tmp_y = point->y;
	point->x = tmp_x * cos(angle) - tmp_y * sin(angle);
	point->y = tmp_x * sin(angle) + tmp_y * cos(angle);
}

void	rotate_map(t_mlx *mlx_instance, t_map *map, t_rotation rotation)
{
	int	h;
	int	w;

	h = 0;
	while (h < map->height)
	{
		w = 0;
		while (w < map->width)
		{
			if (rotation.x_angle)
				apply_rotation_x(&map->grid[h][w], rotation.x_angle);
			if (rotation.y_angle)
				apply_rotation_y(&map->grid[h][w], rotation.y_angle);
			if (rotation.z_angle)
				apply_rotation_z(&map->grid[h][w], rotation.z_angle);
			w++;
		}
		h++;
	}
	draw_grid(mlx_instance, map);
}
