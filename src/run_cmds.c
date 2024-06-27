/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:24:34 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/27 18:52:44 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/libft.h"
#include <fcntl.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>

int	run_cmd(t_pipes *p, char *cmd[], char *env[])
{
	size_t	i;
	char	*abs_cmd;
	int		fd_in;
	int		fd_out;

	fd_in =  p->fd[p->n_cmd % 2][0];
	fd_out = p->fd[(p->n_cmd + 1) % 2][1];
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	ft_close(p, fd_in);
	ft_close(p, fd_out);
	if (cmd[0][0] == '/' || (cmd[0][0] == '.' && cmd[0][1] == '/'))
		if (execve(cmd[0], cmd, env))
			stop_error(ft_strjoin(cmd[0], ": command not found"), 127, p, 0);
	i = 0;
	while (p->paths[i])
	{
		abs_cmd = ft_strjoin_free(ft_strjoin(p->paths[i], "/"), cmd[0], 1, 0);
		execve(abs_cmd, cmd, env);
		free(abs_cmd);
		i++;
	}
	return (stop_error(ft_strjoin(cmd[0], ": command not found"), 127, p, 0));
}

int	run_first(t_pipes *p, char *av[], char *env[])
{
	pid_t	pid;
	char	**cmd;

	if (pipe(p->fd[1]) == -1)
		stop_error("pipe error", EXIT_FAILURE, p, true);
	cmd = ft_split(av[2 + p->here_doc], ' ');
	if (!cmd)
		stop_error("split", EXIT_FAILURE, p, true);
	pid = fork();
	if (pid == -1)
		stop_error("fork error", EXIT_FAILURE, p, true);
	if (pid == 0)
	{
		if (!p->here_doc && get_infile(p, av))
			exit(EXIT_FAILURE);
		else if (p->here_doc)
			ft_close(p, p->fd[0][1]);
		ft_close(p, p->fd[1][0]);
		return (run_cmd(p, cmd, env));
	}
	p->n_cmd++;
	free_split(cmd);
	return (0);
}

int	run_last(t_pipes *p, char *av[], char *env[])
{
	pid_t	pid;
	char	**cmd;
	int		wstatus;

	pid = fork();
	if (pid == -1)
		stop_error("fork error", EXIT_FAILURE, p, true);
	cmd = ft_split(av[0], ' ');
	if (!cmd)
		stop_error("split", EXIT_FAILURE, p, true);
	if (pid == 0)
	{
		get_outfile(p, av[1]);
		ft_close(p, p->fd[p->n_cmd % 2][1]);
		return (run_cmd(p, cmd, env));
	}
	free_split(cmd);
	ft_close(p, p->fd[p->n_cmd % 2][0]);
	ft_close(p, p->fd[p->n_cmd % 2][1]);
	waitpid(pid, &wstatus, 0);
	wait(NULL);
	/* ft_close(p, p->fd[(p->n_cmd - 1) % 2][1]); */
	return (WEXITSTATUS(wstatus));
}

int	run_middle(t_pipes *p, char *av[], char *env[])
{
	int		i;
	pid_t	pid;
	char	**cmd;

	i = 3 + p->here_doc;
	while (av[i] && av[i + 1] && av[i + 2])
	{
		if (pipe(p->fd[(p->n_cmd - 1) % 2]) == -1)
			stop_error("pipe", EXIT_FAILURE, p, true);
		write(1, "here\n", 5);
		pid = fork();
		if (pid == -1)
			stop_error("fork error", EXIT_FAILURE, p, true);
		if (pid == 0)
		{
			cmd = ft_split(av[i], ' ');
			if (!cmd)
				stop_error("split", EXIT_FAILURE, p, true);
			ft_close(p, p->fd[p->n_cmd % 2][1]);
			ft_close(p, p->fd[(p->n_cmd - 1) % 2][0]);
			return (run_cmd(p, cmd, env));
		}
		ft_close(p, p->fd[p->n_cmd % 2][0]);
		ft_close(p, p->fd[p->n_cmd % 2][1]);
		i++;
		p->n_cmd++;
	}
	return (0);
}

int	run_all(t_pipes *p, char *av[], char *env[])
{
	if (p->here_doc)
	{
		if (pipe(p->fd[0]) == -1)
			stop_error("pipe error", EXIT_FAILURE, p, false);
		get_here_doc(p, av);
	}
	if (run_first(p, av, env) == 1)
		p->n_cmd++;
	run_middle(p, av, env);
	return (run_last(p, &av[p->n_cmd + 2 + p->here_doc], env));
}
