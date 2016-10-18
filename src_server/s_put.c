/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_put.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-floc <ale-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 17:51:53 by ale-floc          #+#    #+#             */
/*   Updated: 2015/04/02 17:51:54 by ale-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	usageargc(int argc, char **argv)
{
	if (argc != 2)
		usage(argv[0]);
}

int		put_exist(t_client *client)
{
	int				file;
	DIR				*path;
	struct dirent	*sd;

	file = 0;
	sd = NULL;
	path = NULL;
	path = opendir(client->pwd);
	while ((sd = readdir(path)) != NULL)
	{
		if (!ft_strncmp(sd->d_name, client->buf, ft_strlen(sd->d_name) + 1))
		{
			ft_sleep(3000000);
			send(client->cs, "exist", 5 + 1, 0);
			printf("[%s] [put] \033[33m%s \033[31m(failure)\033[00m\n",
					client->name, client->buf);
			return (-1);
		}
	}
	return (1);
}

void	create_put(t_client *client, char *file)
{
	int		mode;
	int		size;
	int		ret;
	char	buff[BUFSIZE];
	int		nb_read;

	nb_read = 0;
	mode = 0;
	ft_sleep(2900000);
	send(client->cs, "isok", 5 + 1, 0);
	recv(client->cs, client->buf, BUFSIZE - 1, 0);
	size = ft_atoi(client->buf);
	recv(client->cs, client->buf, BUFSIZE - 1, 0);
	mode = ft_atoi(client->buf);
	client->fd = open(file, O_WRONLY | O_CREAT, mode);
	while ((ret = recv(client->cs, buff, BUFSIZE - 1, 0)) > 0)
	{
		buff[ret] = '\0';
		nb_read += ret;
		write(client->fd, buff, ret);
		if (nb_read == size)
			break ;
	}
}

void	cmd_put(t_client *client, t_build *build)
{
	int		good;
	char	*file;

	good = 0;
	if ((good = recv(client->cs, client->buf, BUFSIZE - 1, 0)) != 0)
	{
		if (!ft_strncmp(client->buf, "good", 4))
		{
			recv(client->cs, client->buf, BUFSIZE - 1, 0);
			file = ft_strdup(client->buf);
			if (put_exist(&(*client)) == 1)
			{
				create_put(&(*client), file);
				printf("[%s] [put] \033[33m%s \033[32m(succeed)\033[00m\n",
						client->name, file);
			}
		}
		else
			printf("[%s] [put] \033[31mAttempt to put a wrong file\033[00m\n",
					client->name);
	}
}
