/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+      */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+            */
/*   Created: 2024/12/16 22:45:00 by peda-cos          #+#    #+#              */
/*   Updated: 2024/12/16 23:59:59 by peda-cos         ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void	close_safe(int *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}

int	safe_exit_on_error(void *ptr1, void *ptr2, int fd, int ret_code)
{
	if (ptr1)
		free(ptr1);
	if (ptr2)
		free(ptr2);
	if (fd != -1)
		close(fd);
	return (ret_code);
}
