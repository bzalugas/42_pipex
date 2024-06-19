/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:11:46 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/19 13:58:12 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include "../include/pipex.h"
#include "../include/libft.h"
#include <unistd.h>

char	**get_paths(char *env[])
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return(ft_split(&env[i][5], ':'));
		i++;
	}
	return (NULL);
}

int	run_cmd1(int fd[2], char *av[], char *env[])
{
	int		fd_infile;
	char	**paths;
	size_t	i;
	char	**cmd_options;
	char	*cmd;

	(void)fd;
	if (access(av[1], F_OK | R_OK) == -1)
		return (stop_perror(av[1], 0));
	fd_infile = open(av[1], O_RDONLY);
	if (fd_infile == -1)
		return (stop_perror(av[1], 0));
	dup2(fd_infile, STDIN_FILENO);
	paths = get_paths(env);
	if (!paths)
		return (stop_error("get_paths"));
	cmd_options = ft_split(av[2], ' ');
	if (!cmd_options)
		return (stop_error("split command"));
	i = 0;
	while (paths[i])
	{
		cmd = ft_strjoin_free(ft_strjoin(paths[i], "/"), cmd_options[0], 1, 0);
		execve(cmd, cmd_options, env);
		free(cmd);
		i++;
	}
	stop_error(ft_strjoin("Command not found: ", cmd_options[0]));
	return (0);
}

int	main(int ac, char *av[], char *env[])
{
	pid_t	pid;
	int		fd[2];

	if (ac != 5)
		stop_perror("Wrong arguments number", EINVAL);
	if (pipe(fd) == -1)
		stop_perror("Pipe error", 0);
	pid = fork();
	if (pid == -1)
		stop_perror("Fork error", 0);
	if (pid == 0)
		run_cmd1(fd, av, env);
	return (0);
}
