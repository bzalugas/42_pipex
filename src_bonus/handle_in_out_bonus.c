/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_in_out_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:33:17 by bazaluga          #+#    #+#             */
/*   Updated: 2024/07/05 10:40:10 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"
#include "../include/libft.h"
#include <fcntl.h>
#include <stdbool.h>

int	get_here_doc(t_pipes *p, char *av[])
{
	char	*line;
	char	*lim;

	lim = ft_strjoin(av[2], "\n");
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (!ft_strncmp(lim, line, ft_strlen(line)))
		{
			free(line);
			free(lim);
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
	int	fdn;

	fdn = (p->n_cmd - 1) % 2;
	if (p->here_doc)
		p->fd[fdn][1] = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		p->fd[fdn][1] = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p->fd[fdn][1] == -1)
		stop_perror(filename, 0, p, true);
	return (0);
}
