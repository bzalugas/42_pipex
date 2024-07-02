/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:24:34 by bazaluga          #+#    #+#             */
/*   Updated: 2024/07/02 11:48:32 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/libft.h"

static int	run_cmd(t_pipes *p, char *cmd[], char *env[])
{
	size_t	i;
	char	*abs_cmd;

	dup2(p->fd_in, STDIN_FILENO);
	dup2(p->fd_out, STDOUT_FILENO);
	ft_close(p, p->fd_in);
	ft_close(p, p->fd_out);
	if (cmd[0][0] == '/' || (cmd[0][0] == '.' && cmd[0][1] == '/'))
		if (execve(cmd[0], cmd, env))
			stop_perror(cmd[0], 0, p, 1);
	i = 0;
	while (p->paths && p->paths[i])
	{
		abs_cmd = ft_strjoin(p->paths[i], cmd[0]);
		execve(abs_cmd, cmd, env);
		free(abs_cmd);
		i++;
	}
	return (stop_error(cmd[0], 127, p, 1));
}

int	run_first(t_pipes *p, char *av[], char *env[])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		stop_error("fork error", EXIT_FAILURE, p, true);
	if (pid == 0)
	{
		ft_close(p, p->fd[0]);
		get_infile(p, av[1]);
		p->fd_out = p->fd[1];
		p->cmd_opts = ft_split(av[2], ' ');
		if (!p->cmd_opts)
			stop_error("split", EXIT_FAILURE, p, true);
		return (run_cmd(p, p->cmd_opts, env));
	}
	return (0);
}

int	run_last(t_pipes *p, char *av[], char *env[])
{
	p->last = fork();
	if (p->last == -1)
		stop_error("fork error", EXIT_FAILURE, p, true);
	if (p->last == 0)
	{
		ft_close(p, p->fd[1]);
		get_outfile(p, av[1]);
		p->fd_in = p->fd[0];
		p->cmd_opts = ft_split(av[0], ' ');
		if (!p->cmd_opts)
			stop_error("split", EXIT_FAILURE, p, true);
		return (run_cmd(p, p->cmd_opts, env));
	}
	return (0);
}
