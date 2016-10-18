/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_get.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-floc <ale-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 13:55:28 by ale-floc          #+#    #+#             */
/*   Updated: 2015/04/02 17:20:41 by ale-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		send_read_file(t_client *client, int file)
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
			bytes = send(client->cs, buff, fd, 0);
			size = fd + size;
		}
		fd = read(file, buff, BUFSIZE - 1);
	}
	return (size);
}

void	get_file(t_client *client, t_build *build, char *file)
{
	int				fd;
	char			*permission;
	char			*size;
	struct stat		st;

	fd = open(file, O_RDONLY);
	fstat(fd, &st);
	permission = ft_itoa(st.st_mode);
	size = ft_itoa(st.st_size);
	ft_sleep(4000000);
	send(client->cs, "good", 4 + 1, 0);
	recv(client->cs, client->buf, BUFSIZE - 1, 0);
	if (!ft_strncmp("exist", client->buf, 6))
		printf("[%s] [get] \033[31mAttempt to get a wrong file or nothing\
				\033[00m\n", client->name);
	if (!ft_strncmp("isok", client->buf, 5))
	{
		onyest(&(*client), size, permission);
		fd = send_read_file(&(*client), fd);
		printf("[get] \033[33m%s \033[32m%d bytes (succeed)\
				\033[00m\n", file, fd);
		if (st.st_size == 0)
			send(client->cs, "\0", 1, 0);
	}
}

int		get_file_exist(t_client *client, t_build *build)
{
	int				file;
	int				mode;
	struct stat		st;
	DIR				*path;
	struct dirent	*sd;

	mode = 0;
	sd = NULL;
	path = NULL;
	path = opendir(".");
	file = open(build->split[1], O_RDONLY, S_IRWXU | S_IRWXO | S_IRWXG);
	if (file == -1)
	{
		while ((sd = readdir(path)) != NULL)
		{
			if (!ft_strncmp(sd->d_name, build->split[1],
						ft_strlen(sd->d_name) + 1))
				file = 1;
		}
		if (letsgo(&(*client), &(*build), file) == -1)
			return (-1);
	}
	return (file);
}

int		check_get_end(t_client *client, t_build *build, char *file)
{
	struct stat		filestat;
	int				test;
	DIR				*dossier;

	test = 0;
	dossier = NULL;
	chdir(".");
	if ((test = get_file_exist(&(*client), &(*build))) != -1)
	{
		fstat(test, &filestat);
		if (!S_ISDIR(filestat.st_mode))
			get_file(&(*client), &(*build), file);
		else
		{
			send(client->cs, "[get] can't not get a folder !...", 34, 0);
			return (1);
		}
	}
	close(test);
	return (1);
}

void	cmd_get(t_client *client, t_build *build)
{
	int		ok;
	char	*file;

	ok = 0;
	if ((ok = recv(client->cs, client->buf, BUFSIZE - 1, 0)) != 0)
	{
		if (!ft_strncmp(client->buf, "ok", 4))
		{
			file = ft_strdup(build->split[1]);
			if (check_get_end(&(*client), &(*build), file) == 1)
				ft_sleep(5000000);
		}
		else
			printf("[%s] [get] \033[31mAttempt to put a wrong file or nothing\
					\033[00m\n", client->name);
	}
}
