/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_run.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-floc <ale-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 13:45:26 by ale-floc          #+#    #+#             */
/*   Updated: 2015/04/02 14:56:39 by ale-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	ft_fork(char *folder, t_client *client, t_build *build)
{
	pid_t pid;

	pid = fork();
	if (!pid)
	{
		dup2(client->cs, 2);
		dup2(client->cs, 1);
		execve(folder, build->split, NULL);
	}
	else
	{
		printf("[%s] Request Send\n", client->name);
		wait(0);
	}
}

int		ft_run(t_client client)
{
	t_build		build;
	char		*folder;
	int			i;

	i = 0;
	client.pwd = getcwd(NULL, 0);
	printf("[%s] Received %d bytes (%s)\n", client.name, client.r, client.buf);
	build.split = ft_strsplit_fn(client.buf, &is_space_or_tab);
	if (build.split[0] == '\0')
		return (0);
	check_cmd(&client, &build, folder);
	ft_sleep(40000000);
	send(client.cs, "\0", 1, 0);
	return (0);
}

char	*check_binaire(t_client *e, char *line)
{
	DIR				*file;
	struct dirent	*sd;
	char			*str;
	int				i;

	i = 0;
	while (e->path[i])
	{
		file = opendir(e->path[i]);
		if (file)
		{
			while ((sd = readdir(file)) != NULL)
			{
				if (!ft_strcmp(sd->d_name, line))
				{
					str = ft_strjoin(e->path[i], ft_strjoin("/", line));
					closedir(file);
					return (str);
				}
			}
			closedir(file);
		}
		i++;
	}
	return (0);
}

void	check_cmd(t_client *client, t_build *build, char *folder)
{
	if (!ft_strncmp("cd", build->split[0], 2))
		ft_cd(&(*client), &(*build));
	else if (!ft_strncmp("put", build->split[0], 4))
		cmd_put(&(*client), &(*build));
	else if (!ft_strncmp("get", build->split[0], 4))
		cmd_get(&(*client), &(*build));
	else if (!ft_strncmp("lls", build->split[0], 4))
		printf("[%s] Print lls \033[32m(succeed)\033[00m !\n", client->name);
	else if (!ft_strncmp("ls", build->split[0], 3) ||
			!ft_strncmp("pwd", build->split[0], 4) ||
		!ft_strncmp("rm", build->split[0], 3) ||
		!ft_strncmp("mkdir", build->split[0], 6))
	{
		folder = check_binaire(&(*client), build->split[0]);
		ft_fork(folder, &(*client), &(*build));
	}
	else
		cmd_notfound_nc(&(*client), &(*build));
}

void	cdwithslash(t_build *build, t_client *client, char *tmp)
{
	client->pwd = getcwd(NULL, 0);
	if (ft_strncmp("/", build->split[1], 1))
		client->pwd = ft_strjoin(client->pwd,
				ft_strjoin("/", build->split[1]));
	else
		client->pwd = ft_strjoin(client->pwd, build->split[1]);
	ft_error_cd(client, client->pwd, tmp);
}
