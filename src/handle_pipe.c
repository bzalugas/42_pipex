/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:24:41 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/25 11:24:45 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <unistd.h>
#include <fcntl.h>

void	handle_pipe(t_pipes *p)
{
	if (p->n_cmd % 2 == 0)
	{
		p->fd_in = p->fd1[0];
		p->fd_out = p->fd2[1];
		close(p->fd1[1]);
		close(p->fd2[0]);
	}
	else
	{
		p->fd_in = p->fd2[0];
		p->fd_out = p->fd1[1];
		close(p->fd1[0]);
		close(p->fd2[1]);
	}
}
