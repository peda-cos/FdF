/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 00:43:15 by peda-cos          #+#    #+#             */
/*   Updated: 2024/11/28 01:10:26 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ft_free_tab(void **tab, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->grid2d)
		ft_free_tab((void **)map->grid2d, map->rows);
	if (map->grid3d)
		ft_free_tab((void **)map->grid3d, map->rows);
	free(map);
}

void	handle_error(const char *message)
{
	if (errno == 0)
	{
		ft_putstr_fd("FdF: ", 2);
		ft_putstr_fd((char *)message, 2);
		ft_putchar_fd('\n', 2);
	}
	else
		perror("FdF");
	exit(1);
}

void	error_map(int fd, t_map *map, char *message)
{
	close(fd);
	free_map(map);
	handle_error(message);
}
