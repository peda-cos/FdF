/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 20:01:38 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/28 21:37:38 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_string_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	exit_with_error(char *error_message)
{
	if (errno == 0)
	{
		ft_putstr_fd("\n", 2);
		ft_putendl_fd(error_message, 2);
	}
	else
		perror(error_message);
	exit(1);
}
