/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:33:54 by bazaluga          #+#    #+#             */
/*   Updated: 2024/07/01 18:36:16 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/libft.h"
#include <errno.h>
#include <stdio.h>

int	end_pipex(t_pipes *p, int exit_code, bool close_fds)
{
	if (p->paths)
		free_split(p->paths);
	if (p->cmd_opts)
		free_split(p->cmd_opts);
	free(p->prog_name);
	if (close_fds)
	{
		if (p->fd[0] != -1)
			ft_close(p, p->fd[0]);
		if (p->fd[1] != -1)
			ft_close(p, p->fd[1]);
	}
	exit(exit_code);
}

int	stop_perror(char *msg, int error, t_pipes *p, bool close_fds)
{
	char	*buf;

	if (error != 0)
		errno = error;
	else
		error = EXIT_FAILURE;
	buf = ft_strjoin(p->prog_name, msg);
	perror(buf);
	free(buf);
	return (end_pipex(p, error, close_fds));
}

int	stop_error(char *msg, int error, t_pipes *p, bool close_fds)
{
	char	*buf;

	buf = ft_strjoin(p->prog_name, msg);
	if (error == 127)
	{
		ft_putstr_fd(buf, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
	}
	else
		ft_putendl_fd(buf, STDERR_FILENO);
	free(buf);
	return (end_pipex(p, error, close_fds));
}
