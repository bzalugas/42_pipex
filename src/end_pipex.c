/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:33:54 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/25 11:48:43 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/libft.h"
#include <errno.h>
#include <stdio.h>

static int fd_in_not_pipe(t_pipes *p)
{
	return (p->fd_in != p->fd1[0] && p->fd_in != p->fd1[1]
		&& p->fd_in != p->fd2[0] && p->fd_in != p->fd2[1]);
}

static int fd_out_not_pipe(t_pipes *p)
{
	return (p->fd_out != p->fd1[0] && p->fd_out != p->fd1[1]
		&& p->fd_out != p->fd2[0] && p->fd_out != p->fd2[1]);
}

int	end_pipex(t_pipes *p, int exit_code, bool close_fds)
{
	int	i;

	i = 0;
	if (p->paths)
	{
		i = 0;
		while (p->paths[i])
		{
			free(p->paths[i]);
			i++;
		}
		free(p->paths);
	}
	if (close_fds)
	{
		close(p->fd1[0]);
		close(p->fd1[1]);
		close(p->fd2[0]);
		close(p->fd2[1]);
		if (fd_in_not_pipe(p))
			close(p->fd_in);
		if (fd_out_not_pipe(p))
			close(p->fd_out);
	}
	exit(exit_code);
}

int	stop_perror(char *msg, int error, t_pipes *p, bool close_fds)
{
	if (error != 0)
		errno = error;
	perror(msg);
	return (end_pipex(p, errno, close_fds));
}

int	stop_error(char *msg, int error, t_pipes *p, bool close_fds)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	return (end_pipex(p, error, close_fds));
}
