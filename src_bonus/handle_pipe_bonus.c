/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:35:00 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/30 14:35:06 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>

int	ft_close(t_pipes *p, int fd)
{
	if (fd == -1)
		return (-1);
	if (p->fd[0][0] == fd)
		p->fd[0][0] = -1;
	if (p->fd[0][1] == fd)
		p->fd[0][1] = -1;
	if (p->fd[1][0] == fd)
		p->fd[1][0] = -1;
	if (p->fd[1][1] == fd)
		p->fd[1][1] = -1;
	return (close(fd));
}

void	close_in_pipe(t_pipes *p)
{
	ft_close(p, p->fd[p->n_cmd % 2][0]);
	ft_close(p, p->fd[p->n_cmd % 2][1]);
}
