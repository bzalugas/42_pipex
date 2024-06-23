/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:24:34 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/23 17:11:35 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/libft.h"
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

int	run_cmd(t_pipes *p, char *cmd[], char *env[])
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
		//use access to free abs_cmd before execve
		if (execve(abs_cmd, cmd, env))
			free(abs_cmd);
		i++;
	}
	return (stop_error(ft_strjoin(cmd[0], ": command not found"), p));
}

int	run_first(t_pipes *p, char *av[], char *env[])
{
	char	**cmd_options;

	if (!p->here_doc)
	{
		if (access(av[1], F_OK | R_OK) == -1)
			return (stop_child_perror(av[1], 0));
		p->fd_in = open(av[1], O_RDONLY);
		if (p->fd_in == -1)
			return (stop_child_perror(av[1], 0));
		cmd_options = ft_split(av[2], ' ');
	}
	else
	{
		p->fd_in = p->fd_hd[0];
		close(p->fd_hd[1]);
		cmd_options = ft_split(av[3], ' ');
	}
	p->fd_out = p->fd2[1];
	close(p->fd1[0]);
	close(p->fd1[1]);
	close(p->fd2[0]);
	if (!cmd_options)
		return (stop_error("split command", p));
	return (run_cmd(p, cmd_options, env));
}

int	run_last(t_pipes *p, char *av[], char *env[])
{
	char	**cmd;

	if (!p->here_doc)
		p->fd_out = open(av[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		p->fd_out = open(av[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
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

int	run_middle_cmds(t_pipes *p, char *av[], char *env[])
{
	int	i;
	int	pid;

	i = 3 + p->here_doc;
	while (av[i] && av[i + 1] && av[i + 2])
	{
		pid = fork();
		if (pid == -1)
			return (stop_perror("fork", 0, p));
		if (pid == 0)
		{
			handle_pipe(p);
			run_cmd(p, ft_split(av[i], ' '), env);
		}
		i++;
		p->n_cmd++;
	}
	return (i);
}

int	run_all(t_pipes *p, char *av[], char *env[])
{
	int	pid;
	int	i;

	pid = fork();
	if (pid == -1)
		return (stop_perror("First fork", 0, p));
	if (pid == 0)
		run_first(p, av, env);
	if (pid != 0 && p->here_doc)
		get_here_doc(p, av);
	p->n_cmd++;
	i = run_middle_cmds(p, av, env);
	pid = fork();
	if (pid == -1)
		return (stop_perror("fork", 0, p));
	if (pid == 0)
		run_last(p, &av[i], env);
	return (0);
}