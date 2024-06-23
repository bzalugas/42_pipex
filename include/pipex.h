/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:12:08 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/23 20:09:54 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdbool.h>

typedef struct s_pipes
{
	int		n_cmd;
	int		fd1[2];
	int		fd2[2];
	int		fd_hd[2];
	int		fd_in;
	int		fd_out;
	char	**paths;
	bool	here_doc;
}				t_pipes;

int		stop_child_perror(char *msg, int error);
int		end_pipex(t_pipes *p, int exit_code);
int		stop_perror(char *msg, int error, t_pipes *p);
int		stop_error(char *msg, int error, t_pipes *p);
void	handle_pipe(t_pipes *p);
int		run_all(t_pipes *p, char *av[], char *env[]);
int		get_here_doc(t_pipes *p, char *av[]);

#endif
