/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:48:17 by phartman          #+#    #+#             */
/*   Updated: 2024/07/15 16:33:15 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void signal_handler(int signum)
{
	static int bits_received = 0;
	static unsigned char character =0;

	if (signum == SIGUSR1)
	{
		character <<= 1;
		character |= 1;
	}
	else if (signum == SIGUSR2)
		character <<= 1;

	

	bits_received++;
	if (bits_received == 8)
	{
		if(character == '\0')
		{
			ft_printf("\n");
		}
		else
		{
			ft_printf("%c", character);
			
		}
		bits_received = 0;
		character = 0;
	}
		
}

int main(void)
{
	struct sigaction sa;
	ft_printf("%d\n", getpid());
	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGUSR1, &sa, NULL);
	

	while(1)
	{
		pause();
	}
	return 0;
}
