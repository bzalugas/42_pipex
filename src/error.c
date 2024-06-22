/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:30:13 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/22 18:33:07 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include <errno.h>
#include <stdio.h>
#include "../include/pipex.h"

int	stop_child_perror(char *msg, int error)
{
	if (error != 0)
		errno = error;
	perror(msg);
	exit(errno);
}

int	stop_perror(char *msg, int error, t_pipes *p)
{
	if (error != 0)
		errno = error;
	perror(msg);
	return (end_pipex(p, errno));
}

int	stop_error(char *msg, t_pipes *p)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	return (end_pipex(p, EXIT_FAILURE));
}
