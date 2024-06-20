/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:11:46 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/20 19:38:05 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include "../include/pipex.h"
#include "../include/libft.h"
#include <unistd.h>
#include <sys/wait.h>

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

int	run_cmd(int fd[2], char **paths, char *cmd[], char *env[])
{
	/* size_t	i; */
	/* char	*abs_cmd; */

	(void)paths;
	(void)cmd;
	(void)env;
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);



//PROBLEM HERE : Process is blocked at second fork when trying to read fd[0] or STDIN




	/* char *line = get_next_line(STDIN_FILENO); */
	/* ft_putendl_fd(line, 2); */
	return (0);
	/* i = 0; */
	/* while (paths[i]) */
	/* { */
	/* 	abs_cmd = ft_strjoin_free(ft_strjoin(paths[i], "/"), cmd[0], 1, 0); */
	/* 	if (execve(abs_cmd, cmd, env)) */
	/* 		free(abs_cmd); */
	/* 	i++; */
	/* } */
	/* return (stop_error(ft_strjoin(cmd[0], ": command not found"))); */
}

int	run_first(int fd[2], char **paths, char *av[], char *env[])
{
	int		fd_infile;
	char	**cmd_options;

	if (access(av[1], F_OK | R_OK) == -1)
		return (stop_perror(av[1], 0));
	fd_infile = open(av[1], O_RDONLY);
	if (fd_infile == -1)
		return (stop_perror(av[1], 0));
	dup2(fd_infile, fd[0]);
	cmd_options = ft_split(av[2], ' ');
	if (!cmd_options)
		return (stop_error("split command"));
	return (run_cmd(fd, paths, cmd_options, env));
}

int	run_last(int fd[2], char **paths, char *av[], char *env[])
{
	int		fd_out;
	char	**cmd;

	/* wait(NULL); */
	/* if (access(av[1], F_OK | W_OK) == -1) */
		/* return (stop_perror(av[1], 0)); */
	fd_out = open(av[1], O_WRONLY| O_CREAT | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd_out == -1)
		return (stop_perror(av[1], 0));
	/* dup2(fd[0], STDIN_FILENO); */
	dup2(fd_out, fd[1]);
	cmd = ft_split(av[0], ' ');
	if (!cmd)
		return (stop_error("split command"));
	return (run_cmd(fd, paths, cmd, env));
}

int	main(int ac, char *av[], char *env[])
{
	pid_t	pid;
	int		fd[2];
	char	**paths;

	if (ac != 5)
		stop_perror("Wrong arguments number", EINVAL);
	paths = get_paths(env);
	if (!paths)
		return (stop_error("get_paths"));
	if (pipe(fd) == -1)
		stop_perror("Pipe error", 0);
	pid = fork();
	if (pid == -1)
		stop_perror("Fork error", 0);
	if (pid == 0)
		run_first(fd, paths, av, env);
	else
	{
		waitpid(pid, NULL, 0);
		pid = fork();
		if (pid == 0)
			run_last(fd, paths, &av[3], env);
		else
		{
			write(1, "here\n", 5);
			waitpid(pid, NULL, 0);
			write(1, "here2\n", 6);
		}
	}
	/* else */
	/* { */
	/* 	char buff[4096]; */
	/* 	ft_bzero(buff, 4096); */
	/* 	close(fd[1]); */
	/* 	read(fd[0], &buff, 4096); */
	/* 	close(fd[0]); */
	/* 	write(1, &buff, ft_strlen(buff)); */
	/* } */
	return (0);
}
