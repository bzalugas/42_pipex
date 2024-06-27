/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_in_out.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 00:12:02 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/27 20:19:20 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/libft.h"
#include <fcntl.h>
#include <stdbool.h>

int	get_here_doc(t_pipes *p, char *av[])
{
	char	*line;
	char	*lim;

	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		lim = ft_strnstr(line, av[2], ft_strlen(line));
		if (lim)
		{
			if (line != lim)
				write(p->fd[0][1], line, lim - line);
			free(line);
			close(p->fd[0][1]);
			return (0);
		}
		else
			ft_putstr_fd(line, p->fd[0][1]);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	return (0);
}

int	get_infile(t_pipes *p, char *filename)
{
	p->fd[0][0] = open(filename, O_RDONLY);
	if (p->fd[0][0] == -1)
		stop_perror(filename, 0, p, true);
	return (0);
}

int	get_outfile(t_pipes *p, char *filename)
{
	if (p->here_doc)
		p->fd[(p->n_cmd - 1) % 2][1] = open(filename, O_WRONLY | O_CREAT
			| O_APPEND, 0644);
	else
		p->fd[(p->n_cmd - 1) % 2][1] = open(filename, O_WRONLY | O_CREAT
			| O_TRUNC, 0644);
	if (p->fd[(p->n_cmd - 1) % 2][1] == -1)
		stop_perror(filename, 0, p, true);
	return (0);
}
