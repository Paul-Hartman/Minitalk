# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/03 14:56:36 by phartman          #+#    #+#              #
#    Updated: 2024/07/31 13:47:27 by phartman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := cc
CFLAGS := -Wall -Wextra -Werror

CLIENT_SRCS := client.c
SERVER_SRCS := server.c
HEADERS := -I./minitalk.h

LIBFT := ./ft_printf/libftprintf.a
CLIENT_OBJS := $(CLIENT_SRCS:.c=.o)
SERVER_OBJS := $(SERVER_SRCS:.c=.o)

CLIENT := client
SERVER := server

all: $(CLIENT) $(SERVER)

$(CLIENT): $(CLIENT_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@ -L./ft_printf -lftprintf

$(SERVER): $(SERVER_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@ -L./ft_printf -lftprintf

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C ./ft_printf

clean:
	rm -f $(CLIENT_OBJS) $(SERVER_OBJS)
	$(MAKE) clean -C ./ft_printf

fclean: clean
	rm -f $(CLIENT) $(SERVER)
	$(MAKE) fclean -C ./ft_printf

re: fclean all

.PHONY: all clean fclean re