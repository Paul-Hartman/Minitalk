/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:48:17 by phartman          #+#    #+#             */
/*   Updated: 2024/07/16 18:18:36 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char *reallocate(char *old_str, int len)
{

	char *new_str;
	new_str = malloc(len);
	memcpy(new_str, old_str, strlen(old_str));
	free(old_str);
	return (new_str);
}

void signal_handler(int signum)
{
	static int bits_received = 0;
	static unsigned char character = 0;
	static char *str = NULL;
	static int len = 0;

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
		str = realloc(str, len + 2); // allocate space for the new character and the null terminator
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
	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
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
