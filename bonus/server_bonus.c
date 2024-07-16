/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:27:55 by phartman          #+#    #+#             */
/*   Updated: 2024/07/16 17:33:05 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void signal_handler(int signum, siginfo_t *info, void *context)
{
	static int bits_received = 0;
	static unsigned char character = 0;
	int valid;
	valid = 0;
	(void)context;
	if (signum == SIGUSR1)
	{
		character <<= 1;
		character |= 1;
		valid = kill(info->si_pid, SIGUSR1);
	}
	else if (signum == SIGUSR2)
	{
		character <<= 1;
		valid = kill(info->si_pid, SIGUSR2);
	}
	if(valid == -1)
	{
		ft_printf("Error sending signal\n");
		exit(1);
	}

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
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);

	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGUSR1, &sa, NULL);
	
	sigaddset(&sa.sa_mask, SIGUSR1);
sigaddset(&sa.sa_mask, SIGUSR2);
	while(1)
	{
		pause();
	}
	return 0;
}
