/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@strudent.42berlin.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:48:17 by phartman          #+#    #+#             */
/*   Updated: 2024/07/10 01:34:47 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void signal_handler(int signum)
{
	static int bits_received = 0;
	static char character = 0;

	if (signum == SIGUSR1) {
		character <<= 1; 
	} else if (signum == SIGUSR2) {
		character <<= 1;
		character |= 1; // Add 1
	}

	bits_received++;
	if (bits_received == 8)
	{
		printf("Received character: %c\n", character);
		bits_received = 0;
		character = 0;
	}
}

int main(int argc, char const *argv[])
{
	struct sigaction sa;
	int pid;

	
	if(argc != 1)
	{
		ft_printf("write wrong args\n");
		return 1;
	}
	pid = getpid();
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	while(1)
	{
		pause();
	}
	return 0;
}
