/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:33:54 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/25 11:37:52 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/libft.h"
#include <errno.h>
#include <stdio.h>

int	end_pipex(t_pipes *p, int exit_code)
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
	close(p->fd1[0]);
	close(p->fd1[1]);
	close(p->fd2[0]);
	close(p->fd2[1]);
	close(p->fd_in);
	close(p->fd_out);
	exit(exit_code);
}

int	stop_perror(char *msg, int error, t_pipes *p)
{
	if (error != 0)
		errno = error;
	perror(msg);
	return (end_pipex(p, errno));
}

int	stop_error(char *msg, int error, t_pipes *p)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	return (end_pipex(p, error));
}
