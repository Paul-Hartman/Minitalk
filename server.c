/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:48:17 by phartman          #+#    #+#             */
/*   Updated: 2024/07/22 18:41:07 by phartman         ###   ########.fr       */
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
	int valid;
	(void)context;
	valid = 0;
	
	if (signum == SIGUSR1 || signum == SIGUSR2)
	{
		
		character <<= 1;
		if (signum == SIGUSR1)
			character |= 1;
		//usleep(50);
		//printf("Signal received from %d\n", info->si_pid);
		valid = kill(info->si_pid, SIGUSR1);
		if (valid == -1)
		{
			ft_printf("Error sending signal\n");
			exit(1);
		}
		bits_received++;
	}
	if (bits_received == 8)
	{
		if(character == '\0')
		{
			ft_printf("%s\n", str);
			free(str);
			str = NULL;
			len = 0;
			 bits_received = 0; // Reset bits_received for safety
    		character = 0; // Reset character for safety
		}
		else
		{
			str = reallocate(str, len + 2);
			if (!str)
			{
				ft_printf("Error allocating memory\n");
				exit(1);
			}
			str[len] = character;
			len++;
			str[len] = '\0';
			bits_received = 0;
			character = 0;
		}

		
	}
}

int main(void)
{
	struct sigaction sa;
	ft_printf("%d\n", getpid());
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
    sa.sa_sigaction = signal_handler;
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while(1)
	{
		pause();
	}
	return 0;
}
