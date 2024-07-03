# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/03 14:56:36 by phartman          #+#    #+#              #
#    Updated: 2024/07/03 16:59:58 by phartman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC := cc

CFLAGS := -Wall -Wextra -Werror -g


CLIENT_SRCS := client.c\
		
SERVER_SRCS := server.c\

LIBFT = ./ft_printf/libftprintf.a

CLIENT_OBJS := $(CLIENT_SRCS:.c=.o)

SERVER_SRCS := $(SERVER_SRCS:.c=.o)

client = client

server = server

client: $(CLIENT_OBJS) $(LIBFT) 
	@$(CC) $(CFLAGS) $(CLIENT_OBJS) $(LIBFT) -o $(client) 

server: $(SERVER_OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(SERVER_OBJS) $(LIBFT) -o $(server)
 
all: client server $(LIBFT) 


$(LIBFT):
	@make -C ./ft_printf

run_server: ./server

run_client: ./client 
 
clean:
	@rm -f $(OBJS)
	@make clean -C ./ft_printf
	
fclean: clean
	@make fclean -C ./ft_printf
	@rm -f $(client) $(server)

re: fclean all

.PHONY: all clean fclean re server client run_server run_client
