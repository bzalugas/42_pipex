/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:11:46 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/24 22:21:33 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/libft.h"
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

static char	**get_paths(char *env[])
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (ft_split(&env[i][5], ':'));
		i++;
	}
	return (NULL);
}

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

int	main(int ac, char *av[], char *env[])
{
	t_pipes	p;
	int		res;

	p = (t_pipes){.n_cmd = 0, .paths = NULL, .fd_in = -1, .fd_out = -1};
	if (ac < 5)
		stop_perror("Wrong arguments number", EINVAL, &p);
	p.paths = get_paths(env);
	if (!p.paths)
		return (stop_error("get_paths", EXIT_FAILURE, &p));
	if (pipe(p.fd1) == -1 || pipe(p.fd2) == -1)
		return (stop_perror("Pipes openning", 0, &p));
	if (!ft_strncmp(av[1], "here_doc", 8))
		p.here_doc = true;
	res = run_all(&p, av, env);
	end_pipex(&p, res);
	return (0);
}
