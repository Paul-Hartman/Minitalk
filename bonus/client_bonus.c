/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:25:26 by phartman          #+#    #+#             */
/*   Updated: 2024/07/10 19:13:03 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

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
		usleep(42);
		if(valid == -1)
			return (1);
		i--;
	}
	return (0);
}

void recieve_signal(int signum)
{
	if(signum == SIGUSR1)
		ft_printf("Received 1\n");
	else if(signum == SIGUSR2)
		ft_printf("Recieved 0\n");
}


int	main(int argc, char const *argv[])
{
	int server_pid;
	const char *msg;
	int i;
	int valid;
	struct sigaction sa;
	sa.sa_handler = recieve_signal;
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
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
		valid = send_signal(server_pid, (unsigned char)msg[i]);
		if(valid == 1)
		{
			ft_printf("Error sending signal\n");
			return 1;
		}
		i++;
	}
	send_signal(server_pid, '\0');
	return (0);
}