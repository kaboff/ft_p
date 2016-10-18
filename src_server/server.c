/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-floc <ale-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 17:51:32 by ale-floc          #+#    #+#             */
/*   Updated: 2015/04/02 17:51:33 by ale-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	ft_cd(t_client *client, t_build *build)
{
	char *tmp;

	tmp = getcwd(NULL, 0);
	if (!ft_strncmp("cd", build->split[0], 3) && build->split[1] == NULL)
	{
		if (build->split[1] == NULL)
			chdir(client->home);
	}
	else if (!ft_strncmp("cd", build->split[0], 3) &&
			!ft_strncmp("/", build->split[1], 1) &&
		!chdir(build->split[1]))
	{
		chdir(tmp);
		send(client->cs,
					"\033[31mNot permission to access\033[00m\n", 35 + 1, 0);
	}
	else
		cdwithslash(&(*build), &(*client), tmp);
}

int		ft_error_cd(t_client *e, char *file, char *tmp)
{
	if (!chdir(e->pwd))
	{
		e->pwd = getcwd(NULL, 0);
		if (!ft_strnstr(e->pwd, e->home, ft_strlen(e->home)))
		{
			chdir(tmp);
			send(e->cs,
					"\033[31mNot permission to access\033[00m\n", 35 + 1, 0);
		}
	}
	else if (open(file, O_RDONLY) != -1)
	{
		ft_putstr_fd("cd: not a directory: ", e->cs);
		ft_putstr_fd(file, e->cs);
		ft_putstr_fd("\n", e->cs);
	}
	else if (access(file, F_OK) != 0)
		cd_error_file(&(*e), file);
	else if (access(file, X_OK) != 0)
		cd_error_permission(&(*e), file);
	return (0);
}

int		main(int argc, char **argv, char **env)
{
	t_client	client;
	pid_t		pid;

	usageargc(argc, argv);
	init_client(&client, env, argv[1]);
	while ((client.cs = accept(client.sock,
					(struct sockaddr*)&client.csin, &client.cslen)))
	{
		pid = fork();
		if (!pid)
		{
			ft_newclient(&client);
			while ((client.r = recv(client.cs, client.buf, BUFSIZE - 1, 0)) > 0)
			{
				ft_delchar(&(*client.buf));
				if (client.buf[0] != '\0')
					ft_run(client);
				ft_bzero(client.buf, ft_strlen(client.buf));
			}
			printf("\033[32mClient\033[00m %s \033[32mDisconnect ! (%s)\
					\033[00m\n", client.name, inet_ntoa(client.csin.sin_addr));
		}
	}
	closeguys(&client);
	return (0);
}

void	onyest(t_client *client, char *size, char *permission)
{
	ft_sleep(3000000);
	send(client->cs, size, ft_strlen(size) + 1, 0);
	ft_sleep(3500000);
	send(client->cs, permission, ft_strlen(permission) + 1, 0);
}
