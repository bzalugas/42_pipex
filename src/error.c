/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:30:13 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/19 14:04:11 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include <errno.h>
#include <stdio.h>

int	stop_perror(char *msg, int error)
{
	if (error != 0)
		errno = error;
	perror(msg);
	exit(error);
}

int	stop_error(char *msg)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	/* end_fdf(data, EXIT_FAILURE); */
	exit(EXIT_FAILURE);
}
