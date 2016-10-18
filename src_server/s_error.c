/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-floc <ale-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 14:39:18 by ale-floc          #+#    #+#             */
/*   Updated: 2015/04/02 14:39:57 by ale-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	usage(char *str)
{
	printf("\033[33mUsage: %s <port>\033[00m\n", str);
	exit(-1);
}

void	cmd_notfound_nc(t_client *client, t_build *build)
{
	ft_putstr_fd("Command not Found : ", client->cs);
	ft_putstr_fd(build->split[0], client->cs);
	ft_putstr_fd("\n", client->cs);
}

void	cd_error_permission(t_client *e, char *file)
{
	ft_putstr_fd("cd: permission denied: ", e->cs);
	ft_putstr_fd(file, e->cs);
	ft_putstr_fd("\n", e->cs);
}

void	cd_error_file(t_client *e, char *file)
{
	ft_putstr_fd("cd: No such file or directory: ", e->cs);
	ft_putstr_fd(file, e->cs);
	ft_putstr_fd("\n", e->cs);
}

void	closeguys(t_client *client)
{
	close(client->cs);
	close(client->sock);
}
