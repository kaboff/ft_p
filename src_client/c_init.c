/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-floc <ale-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 13:30:03 by ale-floc          #+#    #+#             */
/*   Updated: 2015/04/02 13:34:09 by ale-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

char	*get_hostname(char **env)
{
	int		i;
	char	*str;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("USER", env[i], 4))
			return (ft_strchr(env[i], '=') + 1);
		if (!ft_strncmp("LOGNAME", env[i], 7))
			return (ft_strchr(env[i], '=') + 1);
		i++;
	}
	return ("You");
}

int		create_client(char *addr, int port, t_env *client)
{
	int						sock;
	struct protoent			*proto;
	struct sockaddr_in		sin;

	if (!ft_strncmp("localhost", addr, ft_strlen("localhost")))
		addr = ft_strdup("127.0.0.1");
	proto = getprotobyname("tcp");
	if (proto == 0)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(addr);
	client->name = inet_ntoa(sin.sin_addr);
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		printf("\033[31mConnect error\033[00m\n");
		exit (2);
	}
	return (sock);
}

void	ft_sleep(int time)
{
	int i;

	i = 0;
	while (i != time)
		i++;
}

void	ft_prompt(char *name)
{
	ft_putstr("(");
	ft_putstr("\033[33m");
	ft_putstr(name);
	ft_putstr("\033[00m)\033[36m@\033[00m<\033[32m");
	ft_putstr("\033[00m> ");
}

void	cmd_lls(t_env *client)
{
	DIR				*path;
	int				test;
	struct dirent	*sd;

	sd = NULL;
	test = 0;
	path = NULL;
	path = opendir(".");
	while ((sd = readdir(path)) != NULL)
		ft_putendl(sd->d_name);
}
