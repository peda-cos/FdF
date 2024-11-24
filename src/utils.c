/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:46:16 by peda-cos          #+#    #+#             */
/*   Updated: 2024/11/24 14:46:18 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	error_exit(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	*safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		error_exit("Memory allocation failed");
	return (ptr);
}

void	free_double_ptr(char **array)
{
	int	index;

	index = 0;
	if (!array)
		return ;
	while (array[index])
	{
		free(array[index]);
		index++;
	}
	free(array);
}
