/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:48:17 by phartman          #+#    #+#             */
/*   Updated: 2024/07/18 18:56:53 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char *reallocate(char *old_str, int len)
{
	char *new_str;
	new_str = malloc(len);
	if (!new_str)
    {
        ft_printf("Error allocating memory\n");
        exit(1);
    }
	if(old_str)
	{
		memcpy(new_str, old_str, strlen(old_str));
		free(old_str);
	}
	else
		new_str[0] = '\0';
	
	return (new_str);
}

void signal_handler(int signum, siginfo_t *info, void *context)
{
	static int bits_received;
	static unsigned char character;
	static char *str = NULL;
	static int len;
	(void)context;
	
	if (signum == SIGUSR1 || signum == SIGUSR2)
	{
		
		character <<= 1;
		if (signum == SIGUSR1)
			character |= 1;
		usleep(300);
		//printf("Signal received from %d\n", info->si_pid);
		kill(info->si_pid, SIGUSR1);
		bits_received++;
	}
	if (bits_received == 8)
	{
		str = reallocate(str, len + 2);
		printf("%c", character);
		if (!str)
		{
			ft_printf("Error allocating memory\n");
			exit(1);
		}
		str[len] = character;
		len++;

		if(character == '\0')
		{
			ft_printf("%s\n", str);
			free(str);
			str = NULL;
			len = 0;
		}

		bits_received = 0;
		character = 0;
	}
}

int main(void)
{
	struct sigaction sa;
	ft_printf("%d\n", getpid());
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
    sa.sa_sigaction = signal_handler;
	//sigaddset(&sa.sa_mask, SIGUSR1);
	//sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while(1)
	{
		pause();
	}
	return 0;
}
