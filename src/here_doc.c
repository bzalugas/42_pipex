/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:38:09 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/25 10:35:13 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/libft.h"

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
				write(p->fd1[1], line, lim - line);
			free(line);
			close(p->fd1[1]);
			return (0);
		}
		else
			ft_putstr_fd(line, p->fd1[1]);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	return (0);
}
