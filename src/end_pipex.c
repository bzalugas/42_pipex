/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:33:54 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/22 18:17:49 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <stdlib.h>
#include <unistd.h>
int	end_pipex(t_pipes *p, int exit_code)
{
	int	i;

	i = 0;
	if (p->paths)
	{
		i = 0;
		while (p->paths[i])
		{
			free(p->paths[i]);
			i++;
		}
		free(p->paths);
	}
	exit(exit_code);
}
