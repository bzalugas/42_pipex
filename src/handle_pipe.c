/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:24:41 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/26 09:33:26 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>

int	ft_close(t_pipes *p, int fd)
{
	if (fd == -1)
		stop_error("trying to close -1", 1, p, false);
	if (p->fd[0][0] == fd)
	{
		if (p->fd[0][0] == -1)
			stop_error("fd[0][0] already closed", 1, p, false);
		else
			p->fd[0][0] = -1;
	}
	else if (p->fd[0][1] == fd)
	{
		if (p->fd[0][1] == -1)
			stop_error("fd[0][1] already closed", 1, p, false);
		else
			p->fd[0][1] = -1;
	}
	else if (p->fd[1][0] == fd)
	{
		if (p->fd[1][0] == -1)
			stop_error("fd[1][0] already closed", 1, p, false);
		else
			p->fd[1][0] = -1;
	}
	else if (p->fd[1][1] == fd)
	{
		if (p->fd[1][1] == -1)
			stop_error("fd[1][1] already closed", 1, p, false);
		else
			p->fd[1][1] = -1;
	}
	return (close(fd));
}
