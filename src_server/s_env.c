/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-floc <ale-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 14:39:02 by ale-floc          #+#    #+#             */
/*   Updated: 2015/04/02 14:43:50 by ale-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		check_pwd(t_client *client)
{
	int		i;
	char	*tmp;

	i = 0;
	while (client->env[i])
	{
		if (!ft_strncmp("PWD", client->env[i], 3))
			tmp = ft_strchr(client->env[i], '=') + 1;
		i++;
	}
	if ((ft_strlen(client->pwd)) > ft_strlen(client->env[i]))
		return (1);
	else
		return (0);
}

void	get_pwd(t_client *client, char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("PWD", env[i], 3))
			client->pwd = ft_strchr(env[i], '=') + 1;
		i++;
	}
	client->pwd = getcwd(NULL, 0);
	client->basehome = client->pwd;
	client->home = client->pwd;
}

void	get_path(t_client *client, char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("PATH", env[i], 4))
			tmp = ft_strchr(env[i], '=') + 1;
		i++;
	}
	client->path = ft_strsplit(tmp, ':');
}

void	get_permission(t_client *client, t_build *build)
{
	ft_putstr_fd("[get] ", client->cs);
	ft_putstr_fd(build->split[1], client->cs);
	ft_putstr_fd(" permission denied\n", client->cs);
}

int		letsgo(t_client *client, t_build *build, int file)
{
	if (file == -1)
	{
		send(client->cs, "[get] ", 6, 0);
		send(client->cs, build->split[1], ft_strlen(build->split[1]), 0);
		send(client->cs, " doesn't exists !...", 21, 0);
	}
	else
		get_permission(&(*client), &(*build));
	return (-1);
}
