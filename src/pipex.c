/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:11:46 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/30 15:13:54 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/libft.h"

static void	*free_broken_split(char **arr, size_t broken_idx)
{
	size_t	i;

	if (!arr)
		return (NULL);
	i = 0;
	while (i < broken_idx)
		free(arr[i++]);
	i++;
	while (arr[i])
		free(arr[i++]);
	return (NULL);
}

static char	**get_paths(char *env[])
{
	size_t	i;
	char	**paths;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (env[i])
		paths = ft_split(&env[i][5], ':');
	else
		return (NULL);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin_free(paths[i], "/", 1, 0);
		if (!paths[i])
			return (free_broken_split(paths, i));
		i++;
	}
	return (paths);
}

int	main(int ac, char *av[], char *env[])
{
	t_pipes	p;
	int		res;

	p = (t_pipes){.fd[0] = -1, .fd[1] = -1, .paths = NULL, .cmd_opts = NULL,
		.last = -1};
	if (ac != 5)
		stop_error("Usage: ./pipex infile cmd1 cmd2 outfile", EXIT_FAILURE, &p,
			false);
	p.paths = get_paths(env);
	if (!p.paths)
		return (stop_error("get_paths", EXIT_FAILURE, &p, false));
	if (pipe(p.fd) == -1)
		stop_error("pipe error", EXIT_FAILURE, &p, true);
	run_first(&p, av, env);
	run_last(&p, &av[3], env);
	ft_close(&p, p.fd[0]);
	ft_close(&p, p.fd[1]);
	waitpid(p.last, &res, 0);
	wait(NULL);
	end_pipex(&p, WEXITSTATUS(res), false);
	return (0);
}
