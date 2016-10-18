/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-floc <ale-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 12:36:53 by ale-floc          #+#    #+#             */
/*   Updated: 2015/04/02 17:36:37 by ale-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <dirent.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft.h"

# define BUFSIZE 2048

typedef struct	s_client
{
	int					port;
	int					sock;
	int					cs;
	int					r;
	unsigned int		cslen;
	char				buf[BUFSIZE];
	struct sockaddr_in	csin;
	char				*pwd;
	char				*basehome;
	char				*home;
	char				**path;
	char				**env;
	char				*name;
	int					fd;
	char				*str;
}				t_client;

typedef struct	s_build
{
	char			**split;
}				t_build;

int				is_space_or_tab(char c);
int				check_pwd(t_client *client);
int				check_argument(t_build *build);
char			**ft_strsplit_fn(char const *s, int (*f) (char));
int				ft_command(t_client *client, t_build *build);
void			get_pwd(t_client *client, char **env);
void			get_path(t_client *client, char **env);
char			*check_binaire(t_client *e, char *line);
void			ft_fork(char *folder, t_client *client, t_build *build);
void			ft_cd(t_client *client, t_build *build);
int				ft_error_cd(t_client *e, char *file, char *tmp);
void			cmd_put(t_client *client, t_build *build);
void			create_put(t_client *client, char *file);
int				put_exist(t_client *client);
void			ft_sleep(int time);
int				ft_run(t_client client);
void			cmd_get(t_client *client, t_build *build);
int				check_get_end(t_client *client, t_build *build, char *file);
int				get_file_exist(t_client *client, t_build *build);
void			get_file(t_client *client, t_build *build, char *file);
int				send_read_file(t_client *client, int file);
void			ft_newclient(t_client *client);
void			init_client(t_client *client, char **env, char *str);
void			ft_delchar(char *str);
int				create_server(int port);
void			cmd_notfound_nc(t_client *client, t_build *build);
void			usage(char *str);
void			cd_error_permission(t_client *e, char *file);
void			cd_error_file(t_client *e, char *file);
void			closeguys(t_client *e);
void			check_cmd(t_client *client, t_build *build, char *folder);
void			usageargc(int argc, char **argv);
void			cdwithslash(t_build *build, t_client *client, char *tmp);
void			get_permission(t_client *client, t_build *build);
int				letsgo(t_client *client, t_build *build, int file);
void			onyest(t_client *client, char *size, char *permission);

#endif
