/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:33:53 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/30 14:34:05 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <stdbool.h>

typedef struct s_pipes
{
	int		n_cmd;
	int		fd[2][2];
	char	**paths;
	char	**cmd_opts;
	bool	here_doc;
}				t_pipes;

/* END HANDLING */
int		stop_child_perror(char *msg, int error);
int		end_pipex(t_pipes *p, int exit_code, bool close_fds);
int		stop_perror(char *msg, int error, t_pipes *p, bool close_fds);
int		stop_error(char *msg, int error, t_pipes *p, bool close_fds);

/* Main functions */
int		run_all(t_pipes *p, char *av[], char *env[]);
int		get_here_doc(t_pipes *p, char *av[]);
int		get_infile(t_pipes *p, char *filename);
int		get_outfile(t_pipes *p, char *filename);
void	free_split(char **arr);

/* PIPES & FD HANDLING */
void	handle_pipe(t_pipes *p);
int		ft_close(t_pipes *p, int fd);
void	close_in_pipe(t_pipes *p);

#endif
