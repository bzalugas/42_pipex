/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:12:08 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/30 15:01:54 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdbool.h>
# include <fcntl.h>

typedef struct s_pipes
{
	int		fd[2];
	int		fd_in;
	int		fd_out;
	char	**paths;
	char	**cmd_opts;
	pid_t	last;
}				t_pipes;

/* END HANDLING */
int		end_pipex(t_pipes *p, int exit_code, bool close_fds);
int		stop_perror(char *msg, int error, t_pipes *p, bool close_fds);
int		stop_error(char *msg, int error, t_pipes *p, bool close_fds);

/* Main functions */
int		run_first(t_pipes *p, char *av[], char *env[]);
int		run_last(t_pipes *p, char *av[], char *env[]);
int		get_infile(t_pipes *p, char *filename);
int		get_outfile(t_pipes *p, char *filename);
void	free_split(char **arr);

/* PIPES & FD HANDLING */
int		ft_close(t_pipes *p, int fd);

#endif
