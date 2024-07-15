/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:47:40 by phartman          #+#    #+#             */
/*   Updated: 2024/07/15 19:28:16 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int send_signal(int pid, unsigned char c)
{
	int	i;
	int bit;
	int valid;

	valid = true;
	i = 7;
	while (i >= 0)
	{
		bit = (c >> i) & 1;
		if(bit == 1)
			valid = kill(pid, SIGUSR1);
		else if (bit == 0)
			valid = kill(pid, SIGUSR2);
		usleep(200);
		if(valid == -1)
		{
			ft_printf("Error sending signal\n");
			exit(1);
		}
		i--;
	}
	return (0);
}

int	main(int argc, char const *argv[])
{
	int server_pid;
	const char *msg;
	int i;

	i = 0;

	if (argc != 3)
	{
		ft_printf("wrong number of args\n");
		return 1;
	}
	server_pid = ft_atoi(argv[1]);
	msg = argv[2];

	while(msg[i])
	{
		send_signal(server_pid, (unsigned char)msg[i]);
		i++;
	}
	send_signal(server_pid, '\0');
	return (0);
}
