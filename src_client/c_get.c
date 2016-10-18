/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_get.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-floc <ale-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 13:40:00 by ale-floc          #+#    #+#             */
/*   Updated: 2015/04/02 17:30:39 by ale-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int		ft_command(t_env *client)
{
	t_env *tmp;

	tmp = client;
	client->split = ft_strsplit_fn(tmp->str, &is_space_or_tab);
	if (!client->split[0])
		return (0);
	if (!ft_strncmp("ls", client->split[0], 3))
		return (1);
	if (!ft_strncmp("pwd", client->split[0], 4))
		return (1);
	if (!ft_strncmp("cd", client->split[0], 3))
		return (1);
	if (!ft_strncmp("mkdir", client->split[0], 6))
		return (1);
	if (!ft_strncmp("rm", client->split[0], 3))
		return (1);
	if (!ft_strncmp("quit", client->split[0], 5))
		exit (0);
	if (!ft_strncmp("put", client->split[0], 4))
		return (2);
	if (!ft_strncmp("lls", client->split[0], 4))
		return (3);
	if (!ft_strncmp("get", client->split[0], 4))
		return (4);
	return (0);
}

int		send_read_file(t_env *client, int file)
{
	int		fd;
	int		bytes;
	int		size;
	char	buff[BUFSIZE];

	size = 0;
	ft_sleep(3000000);
	fd = read(file, buff, BUFSIZE - 1);
	while (fd)
	{
		buff[fd] = '\0';
		bytes = 0;
		while (fd - bytes > 0)
		{
			bytes = send(client->sock, buff, fd, 0);
			size = fd + size;
		}
		fd = read(file, buff, BUFSIZE - 1);
	}
	return (size);
}

void	create_get(t_env *client, char *file)
{
	int		mode;
	int		ret;
	char	buff[BUFSIZE];
	int		nb_read;

	nb_read = 0;
	mode = 0;
	ret = 0;
	ft_sleep(2900000);
	send(client->sock, "isok", 5, 0);
	recv(client->sock, client->buff, BUFSIZE - 1, 0);
	client->size = ft_atoi(client->buff);
	recv(client->sock, client->buff, BUFSIZE - 1, 0);
	mode = ft_atoi(client->buff);
	client->fd = open(file, O_WRONLY | O_CREAT, mode);
	while ((ret = recv(client->sock, buff, BUFSIZE - 1, 0)) > 0)
	{
		if (client->size == 0)
			break ;
		buff[ret] = '\0';
		nb_read += ret;
		write(client->fd, buff, ret);
		if (nb_read == client->size)
			break ;
	}
}

int		get_file_exist(t_env *client, char *str)
{
	int				file;
	DIR				*path;
	struct dirent	*sd;

	file = 0;
	path = NULL;
	sd = NULL;
	path = opendir(".");
	while ((sd = readdir(path)) != NULL)
	{
		if (!ft_strncmp(sd->d_name, str, ft_strlen(sd->d_name) + 1))
		{
			ft_sleep(3000000);
			send(client->sock, "exist", 5 + 1, 0);
			printf("[get] \033[33m%s\033[00m already exists...\n", str);
			return (-1);
		}
	}
	return (1);
}

void	check_get(t_env *client)
{
	if (!ft_strncmp("get", client->split[0], 4) && client->split[1] == NULL)
		get_nofile(&(*client));
	else if (!ft_strncmp("get", client->split[0], 4) &&
			client->split[2] != NULL)
		nofilecmd(&(*client));
	else
	{
		client->filee = ft_strdup(client->split[1]);
		if (!ft_strncmp(".", client->split[1], 2) ||
				!ft_strncmp("..", client->split[1], 3))
			get_notcorrect(&(*client));
		else
		{
			cfini(&(*client));
			ft_sleep(5000000);
			client->buff[recv(client->sock, client->buff, BUFSIZE - 1, 0)] = 0;
			if (!ft_strncmp("good", client->buff, 5))
			{
				if (get_file_exist(&(*client), client->filee) == 1)
					create_get(&(*client), client->filee);
			}
			else
				printf("%s\n", client->buff);
		}
	}
}
