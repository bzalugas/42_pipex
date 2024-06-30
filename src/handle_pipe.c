/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:24:41 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/30 14:59:31 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <unistd.h>

int	ft_close(t_pipes *p, int fd)
{
	if (fd == -1)
		return (-1);
	if (p->fd[0] == fd)
		p->fd[0] = -1;
	if (p->fd[1] == fd)
		p->fd[1] = -1;
	return (close(fd));
}
