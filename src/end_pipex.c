/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:33:54 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/25 23:13:17 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/libft.h"
#include <errno.h>
#include <stdio.h>

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
		i = -1;
		while (++i < 2)
		{
			if (p->fd[i][0] != -1)
				ft_close(p, p->fd[i][0]);
			if (p->fd[i][1] != -1)
				ft_close(p, p->fd[i][1]);
		}
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
