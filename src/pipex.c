/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:11:46 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/22 18:24:42 by bazaluga         ###   ########.fr       */
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

int	run_cmd(t_pipes *p,  char *cmd[], char *env[])
{
	size_t	i;
	char	*abs_cmd;

	dup2(p->fd_in, STDIN_FILENO);
	dup2(p->fd_out, STDOUT_FILENO);
	close(p->fd_in);
	close(p->fd_out);
	i = 0;
	while (p->paths[i])
	{
		abs_cmd = ft_strjoin_free(ft_strjoin(p->paths[i], "/"), cmd[0], 1, 0);
		if (execve(abs_cmd, cmd, env))
			free(abs_cmd);
		else
			write(2, "here\n", 5);
		i++;
	}
	return (stop_error(ft_strjoin(cmd[0], ": command not found"), p));
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

int	run_first(t_pipes *p, char *av[], char *env[])
{
	char	**cmd_options;

	if (access(av[1], F_OK | R_OK) == -1)
		return (stop_child_perror(av[1], 0));
	p->fd_in = open(av[1], O_RDONLY);
	if (p->fd_in == -1)
		return (stop_child_perror(av[1], 0));
	p->fd_out = p->fd2[1];
	close(p->fd1[0]);
	close(p->fd1[1]);
	close(p->fd2[0]);
	cmd_options = ft_split(av[2], ' ');
	if (!cmd_options)
		return (stop_error("split command", p));
	return (run_cmd(p, cmd_options, env));
}

int	run_last(t_pipes *p, char *av[], char *env[])
{
	char	**cmd;

	p->fd_out = open(av[1], O_WRONLY| O_CREAT | O_TRUNC, 0644);
	if (p->fd_out == -1)
		return (stop_perror(av[1], 0, p));
	if (p->n_cmd % 2 == 0)
	{
		p->fd_in = p->fd1[0];
		close(p->fd2[0]);
	}
	else
	{
		p->fd_in = p->fd2[0];
		close(p->fd1[0]);
	}
	close(p->fd1[1]);
	close(p->fd2[1]);
	cmd = ft_split(av[0], ' ');
	if (!cmd)
		return (stop_error("split command", p));
	return (run_cmd(p, cmd, env));
}

int	main(int ac, char *av[], char *env[])
{
	pid_t	pid;
	t_pipes	p;
	/* int		i; */

	p = (t_pipes){.n_cmd = 0, .paths = NULL};
	if (ac != 5)
		stop_perror("Wrong arguments number", EINVAL, &p);
	p.paths = get_paths(env);
	if (!p.paths)
		return (stop_error("get_paths", &p));
	if (pipe(p.fd1) == -1 || pipe(p.fd2) == -1)
		return (stop_perror("Pipes openning", 0, &p));
	pid = fork();
	if (pid == -1)
		return (stop_perror("First fork", 0, &p));
	if (pid == 0)
		run_first(&p, av, env);
	else
	{
		p.n_cmd++;
		/* waitpid(pid, NULL, 0); */
		/* i = 3; */
		/* while (av[i] && av[i + 1] && av[i + 2]) */
		/* { */
		/* 	pid = fork(); */
		/* 	if (pid == -1) */
		/* 		return (stop_perror("fork", 0, &p)); */
		/* 	if (pid == 0) */
		/* 		run_cmd(&p, ft_split(av[i], ' '), env); */
		/* 	else */
		/* 		waitpid(pid, NULL, 0); */
		/* } */
		pid = fork();
		if (pid == -1)
			return (stop_perror("fork", 0, &p));
		if (pid == 0)
			run_last(&p, &av[3], env);
		waitpid(pid, NULL, WNOHANG);
		/* wait(NULL); */
	}
	end_pipex(&p, EXIT_SUCCESS);
	return (0);
}
