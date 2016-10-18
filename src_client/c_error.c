/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-floc <ale-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 13:35:26 by ale-floc          #+#    #+#             */
/*   Updated: 2015/04/02 13:36:43 by ale-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	usage(char *str)
{
	printf("Usage: %s <addr> <port>\n", str);
	exit(-1);
}

void	get_nofile(t_env *client)
{
	printf("Error get : [file]...\n");
	ft_sleep(5000000);
	send(client->sock, "\0", 1, 0);
}

void	get_notcorrect(t_env *client)
{
	ft_putendl("This file is not correct !");
	ft_sleep(4000000);
	send(client->sock, "\0", 1, 0);
}

void	nofilecmd(t_env *client)
{
	printf("Too many file ! 1 file maximum...\n");
	ft_sleep(4000000);
	send(client->sock, "\0", 1, 0);
}

void	while_recv(t_env *src)
{
	send(src->sock, src->str, ft_strlen(src->str) + 1, 0);
	if (ft_command(&(*src)) == 2)
		check_put(&(*src));
	else if (ft_command(&(*src)) == 3)
		cmd_lls(&(*src));
	else if (ft_command(&(*src)) == 4)
		check_get(&(*src));
	while ((src->ret = recv(src->sock, src->buff, BUFSIZE - 1, 0)) > 0)
	{
		src->buff[src->ret] = '\0';
		write(1, src->buff, src->ret);
		if (src->buff[0] == '\0')
			break ;
	}
}
