/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:38:09 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/22 21:31:13 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/libft.h"

static char	*get_here_doc_str(char *av[])
{
	char	*here_doc;
	char	*line;
	char	*lim;

	here_doc = NULL;
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		lim = ft_strnstr(line, av[2], ft_strlen(line));
		if (lim)
			return (ft_strjoin_free(here_doc,
					ft_strndup(line, lim - line), 1, 1));
		else
			here_doc = ft_strjoin_free(here_doc, line, 1, 0);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	return (NULL);
}

int	get_here_doc(t_pipes *p, char *av[])
{
	char	*here_doc;

	here_doc = get_here_doc_str(av);
	close(p->fd_hd[0]);
	ft_putstr_fd(here_doc, p->fd_hd[1]);
	close(p->fd_hd[1]);
	free(here_doc);
	return (0);
}
