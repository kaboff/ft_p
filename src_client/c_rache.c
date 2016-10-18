/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_rache.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-floc <ale-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 13:23:03 by ale-floc          #+#    #+#             */
/*   Updated: 2015/04/02 17:27:38 by ale-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	lineop(t_env *client, char *permission, char *size)
{
	ft_sleep(3000000);
	send(client->sock, size, ft_strlen(size) + 1, 0);
	ft_sleep(3500000);
	send(client->sock, permission, ft_strlen(permission) + 1, 0);
}

void	sendop(t_env *client)
{
	ft_sleep(5000000);
	send(client->sock, "\0", 1, 0);
}

void	cfini(t_env *client)
{
	ft_sleep(5000000);
	send(client->sock, "ok", 2 + 1, 0);
}
