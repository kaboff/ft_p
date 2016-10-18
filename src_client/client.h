/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-floc <ale-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 17:51:05 by ale-floc          #+#    #+#             */
/*   Updated: 2015/04/02 17:51:07 by ale-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/stat.h>
# include "libft.h"

# define BUFSIZE 4096

typedef struct	s_env
{
	int			port;
	int			sock;
	char		buff[BUFSIZE];
	int			ret;
	char		*str;
	char		*name;
	char		**split;
	char		*pwd;
	char		*home;
	char		*file;
	int			fd;
	int			size;
	char		*filee;
}				t_env;

char			**ft_strsplit_fn(char const *s, int (*f) (char));
int				is_space_or_tab(char c);
void			get_nofile(t_env *client);
void			get_notcorrect(t_env *client);
void			usage(char *str);
void			ft_sleep(int time);
void			nofilecmd(t_env *client);
void			while_recv(t_env *src);
int				ft_command(t_env *client);
void			cmd_lls(t_env *client);
void			check_put(t_env *client);
void			check_get(t_env *client);
void			ft_prompt(char *name);
int				create_client(char *addr, int port, t_env *client);
char			*get_hostname(char **env);
int				send_read_file(t_env *client, int file);
void			create_get(t_env *client, char *file);
int				get_file_exist(t_env *client, char *str);
void			check_get(t_env *client);
int				ft_command(t_env *client);
void			lineop(t_env *client, char *permission, char *size);
void			sendop(t_env *client);
void			cfini(t_env *client);

#endif
