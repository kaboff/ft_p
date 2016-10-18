/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-floc <ale-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 13:52:56 by ale-floc          #+#    #+#             */
/*   Updated: 2015/04/02 13:54:45 by ale-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		create_server(int port)
{
	int						sock;
	struct protoent			*proto;
	struct sockaddr_in		sin;

	proto = getprotobyname("tcp");
	if (proto == 0)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		printf("\033[31mBind error\033[00m\n");
		exit (2);
	}
	listen(sock, 42);
	return (sock);
}

void	ft_delchar(char *str)
{
	int i;

	i = 0;
	if (str[i] != '\0')
	{
		while (str[i] != '\0')
			i++;
		i--;
		if (str[i] == '\n')
			str[i] = '\0';
		while (i != 0)
		{
			if (str[i] == '\n')
				str[i] = ' ';
			i--;
		}
	}
}

void	init_client(t_client *client, char **env, char *str)
{
	client->port = 0;
	client->sock = 0;
	client->cslen = sizeof(client->csin);
	client->env = env;
	get_pwd(&(*client), client->env);
	get_path(&(*client), client->env);
	client->home = client->pwd;
	printf("Wait a connection...\n");
	client->port = ft_atoi(str);
	client->sock = create_server(client->port);
}

void	ft_newclient(t_client *client)
{
	client->name = ft_strdup(inet_ntoa(client->csin.sin_addr));
	printf("\033[32mClient accepted from %s !\nnamed : \033[00m%s\n",
	inet_ntoa(client->csin.sin_addr), client->name);
	chdir(client->basehome);
	mkdir(client->name, 0777);
	chdir(client->name);
	client->home = ft_strjoin(client->home, "/");
	client->home = ft_strjoin(client->home, client->name);
}

void	ft_sleep(int time)
{
	int i;

	i = 0;
	while (i != time)
		i++;
}
