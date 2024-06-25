/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:11:46 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/26 01:41:31 by bazaluga         ###   ########.fr       */
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

int	main(int ac, char *av[], char *env[])
{
	t_pipes	p;
	int		res;

	p = (t_pipes){.n_cmd = 0, .fd[0][0] = -1, .fd[0][1] = -1, .fd[1][0] = -1,
		.fd[1][1] = -1, .paths = NULL};
	if (ac < 5)
		stop_error("Usage: ./pipex infile cmd1 cmd2 outfile", EXIT_FAILURE, &p,
			false);
	if (!ft_strncmp(av[1], "here_doc", 8))
		p.here_doc = true;
	if (p.here_doc && ac < 6)
		stop_perror("Usage: ./pipex here_doc delim cmd1 cmd2 outfile", EINVAL,
			&p, false);
	p.paths = get_paths(env);
	if (!p.paths)
		return (stop_error("get_paths", EXIT_FAILURE, &p, false));
	res = run_all(&p, av, env);
	end_pipex(&p, res, false);
	return (0);
}
