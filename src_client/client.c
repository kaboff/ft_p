/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-floc <ale-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 17:50:22 by ale-floc          #+#    #+#             */
/*   Updated: 2015/04/02 17:50:24 by ale-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int		put_file_exist(t_env *client)
{
	struct dirent	*sd;
	int				file;
	DIR				*path;

	file = 0;
	sd = NULL;
	path = NULL;
	path = opendir(".");
	file = open(client->split[1], O_RDONLY, S_IRWXU | S_IRWXO | S_IRWXG);
	if (file == -1)
	{
		while ((sd = readdir(path)) != NULL)
		{
			if (!ft_strncmp(sd->d_name, client->split[1],
						ft_strlen(sd->d_name) + 1))
				file = 1;
		}
		if (file == -1)
			printf("[put] %s doesn't exists !...\n", client->split[1]);
		else
			printf("[put] %s permission denied\n", client->split[1]);
		sendop(&(*client));
		return (-1);
	}
	return (file);
}

void	put_file(t_env *client)
{
	int			fd;
	char		*permission;
	char		*size;
	struct stat	st;

	fd = open(client->split[1], O_RDONLY);
	fstat(fd, &st);
	permission = ft_itoa(st.st_mode);
	size = ft_itoa(st.st_size);
	client->file = ft_strdup(client->split[1]);
	ft_sleep(5000000);
	send(client->sock, "good", 4 + 1, 0);
	ft_sleep(3000000);
	send(client->sock, client->split[1], ft_strlen(client->split[1]) + 1, 0);
	recv(client->sock, client->buff, BUFSIZE - 1, 0);
	if (!ft_strncmp("exist", client->buff, 6))
		printf("[put] \033[33m%s\033[00m already exists...\n", client->file);
	if (!ft_strncmp("isok", client->buff, 5))
	{
		lineop(&(*client), permission, size);
		fd = send_read_file(&(*client), fd);
		printf("[put] \033[33m%s \033[32m%d bytes (succeed)\
				\033[00m\n", client->file, fd);
	}
}

void	check_put_end(t_env *client)
{
	struct stat		filestat;
	int				file;
	DIR				*dossier;

	dossier = NULL;
	file = 0;
	chdir(".");
	if ((file = put_file_exist(&(*client))) != -1)
	{
		fstat(file, &filestat);
		if (!S_ISDIR(filestat.st_mode))
			put_file(&(*client));
		else
		{
			printf("[put] can't not put a folder !...\n");
			ft_sleep(5000000);
			send(client->sock, "\0", 1, 0);
		}
	}
}

void	check_put(t_env *client)
{
	if (!ft_strncmp("put", client->split[0], 4) && client->split[1] == NULL)
	{
		printf("Error usage : put [file]...\n");
		ft_sleep(4000000);
		send(client->sock, "\0", 1, 0);
	}
	else if (!ft_strncmp("put",
				client->split[0], 4) && client->split[2] != NULL)
		nofilecmd(&(*client));
	else
	{
		if (!ft_strncmp(".", client->split[1], 2) ||
				!ft_strncmp("..", client->split[1], 3))
			get_notcorrect(&(*client));
		else
			check_put_end(&(*client));
	}
}

int		main(int argc, char **argv, char **env)
{
	t_env src;

	if (argc != 3)
		usage(argv[0]);
	src.port = ft_atoi(argv[2]);
	src.sock = create_client(argv[1], src.port, &src);
	printf("\033[32mConnection Accepted\n\
			\033[00mWelcome \033[32m%s !\033[00m\n", src.name);
	ft_prompt(src.name);
	while ((get_next_line(0, &src.str)))
	{
		if (ft_command(&src) > 0)
			while_recv(&src);
		else
			printf("Command not Found : %s\n", src.str);
		ft_prompt(src.name);
	}
	close(src.sock);
	return (0);
}
