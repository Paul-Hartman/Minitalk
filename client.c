/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:47:40 by phartman          #+#    #+#             */
/*   Updated: 2024/07/22 20:00:57 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_signal_received = 0;

void	send_signal(int pid, unsigned char c)
{
	int	i;
	int	bit;
	int	timeout;

	timeout = 0;
	valid = 0;
	i = 7;
	while (i >= 0)
	{
		bit = (c >> i--) & 1;
		if (bit == 1)
			valid = kill(pid, SIGUSR1);
		else if (bit == 0)
			valid = kill(pid, SIGUSR2);
		if (valid == -1)
		{
			ft_printf("Error sending signal\n");
			exit(1);
		}
		while (!g_signal_received)
		{
			usleep(100);
			timeout += 100;
			if (timeout > 1000000)
			{
				ft_printf("No response received\n");
				exit(1);
			}
		}
		timeout = 0;
		g_signal_received = 0;
	}
}

void	signal_handler(int signum)
{
	if (signum == SIGUSR1)
		g_signal_received = 1;
}

int	main(int argc, char const *argv[])
{
	int					server_pid;
	int					i;
	const char			*msg;
	struct sigaction	sa;

	if (argc == 3)
	{
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = SA_RESTART | SA_SIGINFO;
		sa.sa_handler = signal_handler;
		sigaddset(&sa.sa_mask, SIGUSR1);
		sigaction(SIGUSR1, &sa, NULL);
		i = 0;
		server_pid = ft_atoi(argv[1]);
		msg = argv[2];
		while (msg[i])
			send_signal(server_pid, (unsigned char)msg[i++]);
		send_signal(server_pid, '\0');
	}
	else
		ft_printf("Wrong number of arguments\n");
	return (0);
}
