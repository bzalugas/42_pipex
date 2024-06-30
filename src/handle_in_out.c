/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_in_out.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 00:12:02 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/30 14:59:13 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	get_infile(t_pipes *p, char *filename)
{
	p->fd_in = open(filename, O_RDONLY);
	if (p->fd_in == -1)
		stop_perror(filename, 0, p, true);
	return (0);
}

int	get_outfile(t_pipes *p, char *filename)
{
	p->fd_out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p->fd_out == -1)
		stop_perror(filename, 0, p, true);
	return (0);
}
