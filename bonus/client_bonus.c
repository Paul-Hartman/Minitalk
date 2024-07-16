/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:25:26 by phartman          #+#    #+#             */
/*   Updated: 2024/07/16 17:31:39 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"


volatile sig_atomic_t signal_received = 0;

int send_signal(int pid, unsigned char c)
{
	int	i;
	int bit;
	int valid;
	int timeout;

	timeout = 0;
	valid = true;
	i = 7;
	while (i >= 0)
	{
		signal_received = 0;
		timeout = 0;

		bit = (c >> i) & 1;
		if(bit == 1)
		{
			kill(pid, SIGUSR1);

		}
			
		else if (bit == 0)
		{
			kill(pid, SIGUSR2);
		}

	
		while(!signal_received && timeout <= 600)
		{
			usleep(100);
			timeout += 100;
		}

		if(!signal_received || valid == -1 || timeout > 600)
		{
			ft_printf("Error sending signal\n");
			exit(1);
		}
		i--;
	}
	return (0);
}

void recieve_signal(int signum)
{
	if(signum == SIGUSR1)
	{
		ft_printf("1");
		signal_received = 1;
		
		return;
	}

	else if(signum == SIGUSR2)
	{
		ft_printf("0");
		signal_received = 1;

		return;
	}
	signal_received = 0;
}


int	main(int argc, char const *argv[])
{
	int server_pid;
	const char *msg;
	int i;
	int valid;
	struct sigaction sa;
	sa.sa_handler = recieve_signal;
    sigemptyset(&sa.sa_mask);
		sigaddset(&sa.sa_mask, SIGUSR1);
sigaddset(&sa.sa_mask, SIGUSR2);
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