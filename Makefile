# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ale-floc <ale-floc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/04/02 17:49:57 by ale-floc          #+#    #+#              #
#    Updated: 2015/04/02 17:50:00 by ale-floc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT = client

SERVER = serveur

SRV_F = src_server

C_F = src_client

SRCC = $(C_F)/client.c $(SRV_F)/ft_strsplit_fn.c $(SRV_F)/is_space_or_tab.c $(C_F)/c_error.c $(C_F)/c_init.c $(C_F)/c_get.c $(C_F)/c_rache.c

SRCS = $(SRV_F)/server.c $(SRV_F)/ft_strsplit_fn.c $(SRV_F)/is_space_or_tab.c $(SRV_F)/s_put.c $(SRV_F)/s_env.c $(SRV_F)/s_get.c $(SRV_F)/s_init.c $(SRV_F)/s_error.c $(SRV_F)/s_run.c

OBJC = $(SRCC:.c=.o)

OBJS = $(SRCS:.c=.o)

FLAG = -Wall -Werror -Wextra -ggdb3

LIBFT = libft -lft

INCLUDES = -I libft/includes -I $(SRV_F) -I $(C_F)

.PHONY : libft.a

all : libft.a $(CLIENT) $(SERVER)

libft.a:
	@$(MAKE) -C ./libft

$(CLIENT) : $(OBJC)
	gcc $(FLAG) $(OBJC) $(INCLUDES) -L$(LIBFT) -o $(CLIENT)

$(SERVER) : $(OBJS)
	gcc $(FLAG) $(OBJS) $(INCLUDES) -L$(LIBFT) -o $(SERVER)

%.o: %.c
	gcc $(INCLUDES) -c $< -o $@

clean :
	@make clean -C ./libft
	rm -f $(OBJC)
	rm -f $(OBJS)

fclean : clean
	rm -f libft.a
	rm -f $(SERVER)
	rm -f $(CLIENT)

re : fclean all
