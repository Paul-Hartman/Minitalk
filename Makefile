# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/03 14:56:36 by phartman          #+#    #+#              #
#    Updated: 2024/07/24 19:02:26 by phartman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := cc
CFLAGS := -Wall -Wextra -Werror

CLIENT_SRCS := client.c
SERVER_SRCS := server.c
CLIENT_SRCS_BONUS := bonus/client_bonus.c
SERVER_SRCS_BONUS := bonus/server_bonus.c
HEADERS := -I./minitalk.h

LIBFT := ./ft_printf/libftprintf.a
CLIENT_OBJS := $(CLIENT_SRCS:.c=.o)
SERVER_OBJS := $(SERVER_SRCS:.c=.o)
CLIENT_OBJS_BONUS := $(CLIENT_SRCS_BONUS:.c=.o)
SERVER_OBJS_BONUS := $(SERVER_SRCS_BONUS:.c=.o)


CLIENT := client
SERVER := server
CLIENT_BONUS := client_bonus
SERVER_BONUS := server_bonus

all: $(CLIENT) $(SERVER)



$(CLIENT): $(CLIENT_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@ -L./ft_printf -lftprintf

$(SERVER): $(SERVER_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@ -L./ft_printf -lftprintf

$(CLIENT_BONUS): $(CLIENT_OBJS_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@ -L./ft_printf -lftprintf

$(SERVER_BONUS): $(SERVER_OBJS_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@ -L./ft_printf -lftprintf

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C ./ft_printf

clean:
	rm -f $(CLIENT_OBJS) $(SERVER_OBJS) $(CLIENT_OBJS_BONUS) $(SERVER_OBJS_BONUS)
	$(MAKE) clean -C ./ft_printf

fclean: clean
	rm -f $(CLIENT) $(SERVER) $(CLIENT_BONUS) $(SERVER_BONUS)
	$(MAKE) fclean -C ./ft_printf

re: fclean all

bonus: $(CLIENT_BONUS) $(SERVER_BONUS)

.PHONY: all clean fclean re bonus